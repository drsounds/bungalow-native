#include "SPTableElement.h"

#include "SPSkin.h"
#include "SPGraphicsContext.h"
#include "SPTableDataSource.h"
#include "SPMouseEventArgs.h"
#include "SPEventArgs.h"   // SPKeyEventArgs
#include "SPPlaybackEventArgs.h"  // SPTableRowEventArgs

#include <chrono>

// WXK constants for arrow keys (matches wxWidgets values)
#ifndef WXK_UP
#  define WXK_UP   315
#  define WXK_DOWN 317
#endif

namespace space {
    SPTableElement::SPTableElement()
    {
        //ctor
    }
    void SPTableElement::scroll(int scrollX, int scrollY, int x, int y) {
        SPElement::scroll(scrollX, scrollY, x, y);
    }
    SPTableElement::SPTableElement(SPElement *parent, SPTableDataSource *dataSource)
    {
    	this->setTagName("table");
        //ctor
        this->dataSource = dataSource;
        this->columns = new vector<SPTableColumnHeader *>;
        this->rows = new vector<SPTableRow *>;
        this->addEventListener("mousedown", SPCallback(&SPTableElement::mouseDown), this, this);
    }
    SPTableElement::~SPTableElement()
    {
        //dtor
    }
    string SPTableElement::getType() {
        return "table";
    }
    void SPTableElement::paint(int x, int y, SPGraphicsContext *g) {
        std::vector<SPNode *> *children = this->getChildNodes();
        x += this->getX() ;
        y += this->getY();
        this->absoluteBounds = {
	        x + this->getMargins().left, y + this->getMargins().top, this->getWidth(), this->getHeight()
        };

        int width =  this->getWidth();
        int height = this->getHeight();

        y = y + 1;
        SPTableDataSource *dataSource = this->dataSource;

        // Draw table data here
        width = this->getWidth();
        if (width < 1) {
            width = (this->getParentElement())->getWidth();
        }
        int columnY = y;

        int left = 0;
        int padding = 15;
        int columnWidth = width / dataSource->getColumnCount();
        const int rowH = 18;
        SPColor fgColor = this->getForegroundColor();

        // Draw column headers first (sticky at columnY)
        if (columnY < 60) {
            columnY = this->getParentElement()->getAbsoluteBounds().y + 1;
        }
        m_firstRowY = columnY + rowH;  // remember for hit-testing in mouseDown
        this->getSkin()->drawTableHeader(g, this, x, columnY, width, rowH);
        left = 0;
        for (int i = 0; i < dataSource->getColumnCount(); i++) {
            string text = dataSource->getTextForColumn(i);
            g->drawString(text, SPFontStyle("Tahoma", 13, 1, true, false), fgColor, x + padding + left, columnY + 1, columnWidth, rowH);
            g->drawString(text, SPFontStyle("Tahoma", 13, 1, false, false), fgColor.lighten(-10), x + padding + left, columnY, columnWidth, rowH);
            left += columnWidth;
        }

        // Draw row backgrounds (zebra stripe) then row text
        int rowY = columnY + rowH;
        for (int i = 0; i < dataSource->getRowCount(); i++) {
            this->getSkin()->drawTableRow(g, this, i, x, rowY + i * rowH, width, rowH, i);
        }

        // Full-view mode: extend zebra stripes into the empty area below the last row
        if (this->fullView) {
            int parentBottom = this->getParentElement()->getAbsoluteBounds().y
                             + this->getParentElement()->getHeight();
            int emptyY   = rowY + dataSource->getRowCount() * rowH;
            int ghostRow = dataSource->getRowCount();
            while (emptyY < parentBottom) {
                this->getSkin()->drawTableRow(g, this, ghostRow, x, emptyY, width, rowH, ghostRow);
                emptyY   += rowH;
                ghostRow += 1;
            }
        }

        rowY = columnY + rowH;
        const SPColor selFgColor(95, 132, 180, 255);
        for (int i = 0; i < dataSource->getRowCount(); i++) {
            const SPColor& rowFg = isRowSelected(i) ? selFgColor : fgColor;
            for (int j = 0; j < dataSource->getColumnCount(); j++) {
                string text = dataSource->getTextForCell(j, i);
                left = x + (j * columnWidth) + padding;
                g->drawString(text, SPFontStyle("Tahoma", 13, 1, false, false), rowFg, left, rowY + 1, columnWidth, rowH);
            }
            rowY += rowH;
        }
    }

    // ── Mouse click → row selection + double-click detection ─────────────────
    void SPTableElement::mouseDown(SPObject* sender, SPEventArgs* e) {
        auto *me = dynamic_cast<SPMouseEventArgs *>(e);
        if (!me || !dataSource) return;

        int relY   = me->getY() - m_firstRowY;
        int rowIdx = relY / kRowH;
        int rowCnt = dataSource->getRowCount();

        if (rowIdx < 0 || rowIdx >= rowCnt) return;

        // ── Double-click detection ─────────────────────────────────────────
        auto now = ClockType::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - m_lastClickTime).count();

        if (rowIdx == m_lastClickRow && elapsedMs < kDblClickMs) {
            // Double-click confirmed on same row → dispatch "rowdblclicked"
            auto* dblArgs = new SPTableRowEventArgs(rowIdx);
            this->dispatchEvent("rowdblclicked", dblArgs, this);
            m_lastClickRow  = -1;
            m_lastClickTime = ClockType::time_point{};
        } else {
            m_lastClickRow  = rowIdx;
            m_lastClickTime = now;
        }

        // ── Selection update ───────────────────────────────────────────────
        if (me->getCmdDown()) {
            if (m_selectedRows.count(rowIdx))
                m_selectedRows.erase(rowIdx);
            else
                m_selectedRows.insert(rowIdx);
        } else {
            m_selectedRows.clear();
            m_selectedRows.insert(rowIdx);
        }
        m_anchorRow = rowIdx;
        this->invalidate();
    }

    // ── Keyboard navigation ───────────────────────────────────────────────────
    void SPTableElement::processEvent(const SPEvent& event) {
        if (event.type == "keydown") {
            auto *ke = dynamic_cast<SPKeyEventArgs *>(event.args);
            if (ke && dataSource) {
                int rowCnt = dataSource->getRowCount();
                if (rowCnt == 0) return;

                int next = m_anchorRow;
                if (ke->getKeyCode() == WXK_UP)
                    next = (m_anchorRow <= 0) ? 0 : m_anchorRow - 1;
                else if (ke->getKeyCode() == WXK_DOWN)
                    next = (m_anchorRow + 1 >= rowCnt) ? rowCnt - 1 : m_anchorRow + 1;
                else
                    return;

                m_selectedRows.clear();
                m_selectedRows.insert(next);
                m_anchorRow = next;
                this->invalidate();
            }
            return;
        }
        SPElement::processEvent(event);
    }
}
