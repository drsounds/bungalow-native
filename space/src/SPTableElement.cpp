#include "SPTableElement.h"

#include "SPSkin.h"
#include "SPGraphicsContext.h"
#include "SPTableDataSource.h"

namespace space {
    SPTableElement::SPTableElement()
    {
        //ctor
    }
    void SPTableElement::scroll(int scrollX, int scrollY, int x, int y) {
        SPElement::scroll(scrollX, scrollY, x, y);
    }
    SPTableElement::SPTableElement(SPElement *parent, SPTableDataSource *dataSource) : SPTableElement(parent)
    {
        //ctor
        this->dataSource = dataSource;
    }
    SPTableElement::SPTableElement(SPElement *parent) : SPElement(parent)
    {
    	this->setTagName("table");
        //ctor
        this->columns = new vector<SPTableColumnHeader *>;
        this->rows = new vector<SPTableRow *>;
    }
    SPTableElement::~SPTableElement()
    {
        //dtor
    }
    string SPTableElement::getType() {
        return "table";
    }
    void SPTableElement::paint(int x, int y, SPGraphicsContext *g) {
        sp_position pos;
        std::vector<SPNode *> *children = this->getChildNodes();
        x += this->getX() ;
        y += this->getY();
        this->absoluteBounds = {
	        x + this->getMargins().left, y + this->getMargins().top, this->getWidth(), this->getHeight()
        };

        int width =  this->getWidth();
        int height = this->getHeight();

        sp_rectangle rect2;
        rect2.x = 0;
        rect2.y = 0;
        rect2.width = width;
        rect2.height = height;

        y = y + 1;
        SPTableDataSource *dataSource = this->dataSource;

        // Draw table data here
        width = this->getWidth();
        if (width < 1) {
            width = (this->getParentElement())->getWidth();
        }
        int columnY = y;

        sp_rectangle clipRect;
        clipRect.x = x;
        clipRect.y = y;
        clipRect.width = width;
        clipRect.height = this->getParentElement()->getHeight();
        int left = 0;
        int padding = 10;
        if (dataSource == nullptr) {
            return;
        }
        int columnWidth = width / dataSource->getColumnCount();
        int top = columnY + 18;
        // Draw rows
        for (int i = 0; i < 100; i++) {
            this->getSkin()->drawTableRow(g, this, i, x, y, width, 18, i);
            top += 18;
        }
        int columnYY = columnY;

        top = columnY + 18;
        for (int i = 0; i < dataSource->getRowCount(); i++) {
            for (int j = 0; j < dataSource->getColumnCount(); j++) {
                string text = dataSource->getTextForCell(j, i);
                left = x + (j * columnWidth) + padding;
                g->drawString((string)text.c_str(), SPFontStyle("Tahoma", 13, 1, false, false), SPColor(255, 255, 255, 255), left, top + 2, columnWidth, 18);
            }
            top += 18;
        }

        // Draw column headers
        if (columnY < 60) {
            // If columnY is below zero, set it to the position at top
            columnY = this->getParentElement()->getAbsoluteBounds().y + 1;
        }
        this->getSkin()->drawTableHeader(g, this, 0, 0, width, 18);
        left =0;
        for (int i = 0; i < dataSource->getColumnCount(); i++) {
            string text = dataSource->getTextForColumn(i);
            string str = text.c_str();
            g->drawString(str, SPFontStyle("Tahoma", 13, 1, true, false), SPColor(200, 200, 200, 255), x + padding + left, columnY + 2, columnWidth, 18);
            g->drawString(str, SPFontStyle("Tahoma", 13, 1, true, false), SPColor(0, 0, 0, 255), x + padding + left, columnY + 1, columnWidth, 18);
            left += columnWidth;
        }
        columnY = columnYY;
    }
}
