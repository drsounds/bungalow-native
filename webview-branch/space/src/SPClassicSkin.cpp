//
// Created by Alexander Forselius on 2025-12-11.
//

#include "SPClassicSkin.h"

#include "SPGraphicsContext.h"
#include "SPTableDataSource.h"
#include "libspace.h"
#include "SPAppHeaderElement.h"
#include "SPButtonElement.h"
#include "SPColor.h"

#include <iostream>

using namespace space;

bool SPClassicSkin::drawElement(SPGraphicsContext* g, SPElement *elm, const string& state, const sp_rectangle& bounds)
{
    bool result = false;
    SPColor bgColor = elm->getBackgroundColor();
    SPColor fgColor = elm->getForegroundColor();
    SPColor shadowColor = this->m_shadowColor;
    SPColor *tintColor = elm->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        fgColor = fgColor.tint(*tintColor);
        shadowColor = tintColor->lighten(-0);
    }
    if (elm->getType() == "input") {
        result = true;
    }
    if (elm->getType() == "splitter") {
        result = true;
        bgColor = shadowColor;
        g->fillRectangle(bounds.x, bounds.y, bounds.width, bounds.height, bgColor);
    }
    if (elm->getType() == "button")
    {
    	// cout << "Element id:" << elm->getId();
        result = true;
    	SPColor bgColor = elm->getBackgroundColor();
    	if (tintColor != nullptr) {
    		if (elm->getStringAttribute("variant", "default") == "primary") {
    			bgColor = (*tintColor).alpha(1);
    		} else {
    			bgColor = bgColor.tint(*tintColor);
    		}
    	}
    	if (elm->getColorScheme() == SP_COLOR_SCHEME_DARK) {
    		bgColor = bgColor.lighten(2);
    	}
        SPGradient gradient(
            bgColor.lighten(0.1), bgColor.lighten(-0.2),
            0
        );
        if (state == "active")
        {
            gradient = SPGradient(gradient.getEnd(), gradient.getStart(), 0);
        }
    	if (state == "hover")
    	{
    		gradient = SPGradient(gradient.getStart().lighten(0.01), gradient.getEnd().lighten(0.01), 0);
    	}
        g->fillRoundedLinearGradientRectangle(
            bounds.x,
            bounds.y,
            bounds.width,
            bounds.height,
            25,
            0,
            gradient
        );
    	if (this->m_glossy && state != "active") {
    		SPGradient gradient2(
				bgColor.lighten(0.2), bgColor.lighten(0.3),
				0
				);
    		g->fillRoundedLinearGradientRectangle(
				bounds.x + 5,
				bounds.y + 2,
				bounds.width - 10,
				bounds.height / 2,
				25,
				0,
				gradient2
			);
    		SPGradient gradient3(
				bgColor.lighten(-0.2).alpha(0), bgColor.lighten(0),
				0
				);
    		g->fillRoundedLinearGradientRectangle(
				bounds.x + 10,
				bounds.y + bounds.height / 2 - 2,
				bounds.width - 20,
				bounds.height / 2,
				25,
				0,
				gradient3
			);
    	}
    	g->drawRoundedRectangle(
			bounds.x,
			bounds.y,
			bounds.width,
			bounds.height,
			25,
			bgColor.lighten(-0.5)
    	);
    }
    if (elm->getType() == "table")
    {

    }
    if (elm->getType() == "appheader")
    {
        result = true;
        // Re-get fresh background color (same pattern as button) to avoid
        // double-tinting from the outer bgColor computation at the top.
        SPColor bgColor = elm->getBackgroundColor();
        if (tintColor != nullptr)
            bgColor = bgColor.tint(*tintColor);
        if (elm->getColorScheme() == SP_COLOR_SCHEME_DARK)
            bgColor = bgColor.lighten(2);
        SPGradient gradient(bgColor.lighten(0.1), bgColor.lighten(-0.1), 0);
        g->drawLinearGradient({ bounds.x, bounds.y, bounds.width, bounds.height }, gradient);
    	if (this->m_glossy && state != "active") {
    		SPGradient gradient2(bgColor.lighten(0.2), bgColor.lighten(0), 0);
    		g->drawLinearGradient({ bounds.x, bounds.y + 1, bounds.width, bounds.height / 2 }, gradient2);
    	}
    }
    if (elm->getType() == "appfooter")
    {
        result = true;
        SPGradient gradient(
            bgColor.lighten(0.2), bgColor.lighten(0.1),
            0
        );
        g->drawLinearGradient(
    {
                bounds.x,
                bounds.y,
                bounds.width,
                bounds.height
            },
            gradient
        );
    	if (this->m_glossy && state != "active") {
    		SPGradient gradient2(
				bgColor.lighten(0.2), bgColor.lighten(0.3),
				0
				);
    		g->drawLinearGradient(
				{
					bounds.x,
					bounds.y + 2,
					bounds.width,
					bounds.height / 2,
				},
				gradient2
			);
    		SPGradient gradient3(
				bgColor.lighten(-0.2).alpha(0), bgColor.lighten(0),
				0
			);
    		g->drawLinearGradient(
				{
				bounds.x,
				bounds.y + bounds.height / 2 - 2,
				bounds.width,
				bounds.height / 2,
				},
				gradient3
			);
    	}
    }
    if (elm->getType() == "treeview")
    {
    	if (elm->getColorScheme() == SP_COLOR_SCHEME_DARK) {
    		bgColor = bgColor.lighten(0.28);
    	}
        result = true;
        auto *treeView = dynamic_cast<SPTreeViewElement *>(elm);
        auto width = treeView->getWidth();
        auto height = treeView->getHeight();
        SPGradient gradient(
            bgColor.lighten(0.5), bgColor.lighten(0),
            0
        );
        if (state == "active")
        {
            gradient = SPGradient(SPColor(0, 0, 0, 1), SPColor(10, 10, 10, 0), 0);
        }
        g->fillRectangle(bounds.x, bounds.y, bounds.width, bounds.height, bgColor);
    }
    return result;
}

void SPClassicSkin::drawTableRow(SPGraphicsContext *g, SPTableElement *table, int i, int x, int y, int width, int height, int row)
{
    if (table->isRowSelected(row)) {
        g->fillRectangle(x, y, width, height, SPColor(166, 218, 251, 255));
    } else if (row % 2 == 0) {
        SPColor bgColor = table->getBackgroundColor();
        SPColor *tintColor = table->getTintColor();
        if (tintColor != nullptr)
            bgColor = bgColor.tint(*tintColor);
        // Semi-transparent darker tint for even rows
        SPColor stripeColor = bgColor.lighten(-0.1).alpha(0.35);
        g->fillRectangle(x, y, width, height, stripeColor);
    }
}

void SPClassicSkin::drawTableHeader(SPGraphicsContext* g, SPTableElement *table, int x, int y, int width, int height)
{
    SPColor bgColor = table->getBackgroundColor();
    SPColor *tintColor = table->getTintColor();
    if (tintColor != nullptr)
        bgColor = bgColor.tint(*tintColor);
    if (table->getColorScheme() == SP_COLOR_SCHEME_DARK)
        bgColor = bgColor.lighten(2);

    int colCount = (table->dataSource && table->dataSource->getColumnCount() > 0)
        ? table->dataSource->getColumnCount() : 1;
    int colWidth = width / colCount;

    // Draw each column header cell like a button (default gradient + gloss)
    for (int col = 0; col < colCount; ++col) {
        int cx = x + col * colWidth;
        int cw = (col == colCount - 1) ? (width - col * colWidth) : colWidth;

        // Base button gradient: lighter top → darker bottom
        SPGradient gradient(bgColor.lighten(0.1), bgColor.lighten(-0.2), 0);
        g->drawLinearGradient({cx, y, cw, height}, gradient);

        // Gloss upper highlight
        if (m_glossy) {
            SPGradient gloss(bgColor.lighten(0.25), bgColor.lighten(0.15), 0);
            g->drawLinearGradient({cx + 2, y + 1, cw - 4, height / 2}, gloss);
            SPGradient gloss2(bgColor.lighten(-0.15).alpha(0), bgColor.lighten(0.05), 0);
            g->drawLinearGradient({cx + 2, y + height / 2, cw - 4, height / 2 - 1}, gloss2);
        }

        // Column divider (shadow line on right edge, light line inset)
        SPColor divider = bgColor.lighten(-1.5);
        SPColor dividerLight = bgColor.lighten(1.3);
        if (col < colCount - 1) {
            g->drawLine(cx + cw - 1, y, cx + cw - 1, y + height - 1, divider);
            //g->drawLine(cx + cw,     y, cx + cw,     y + height - 1, dividerLight);
        }
    }

    // Bottom border — same shadow line as button border
    SPColor borderColor = bgColor.lighten(-0.5);
    g->drawLine(x, y + height - 1, x + width, y + height - 1, borderColor);
}

void SPClassicSkin::drawTabBarTab(SPGraphicsContext* g, SPTabBarElement *tabBar, SPTab* tab, int index, bool active, int x, int y, int width, int height)
{
    SPColor bgColor = tabBar->getBackgroundColor();
    SPColor activeBgColor = bgColor; // preserve original for active tab
    SPColor lColor = this->m_lightColor;
    SPColor shadowColor = this->m_shadowColor;
    SPColor* tintColor = tabBar->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        activeBgColor = bgColor;
        shadowColor = tintColor->lighten(-0);
        lColor = lColor.tint(*tintColor).lighten(0.5);
    }
	if (tabBar->getColorScheme() == SP_COLOR_SCHEME_DARK) {
		bgColor = bgColor.lighten(2);
		shadowColor = shadowColor.lighten(-0.2);
	}
    if (active)
    {
        g->fillRectangle(x, y + 1, width, height - 1, activeBgColor);
        if (index > 0)
        {
            g->drawLine(x, y, x, y + height - 1,shadowColor);
        } else {

            g->drawLine(x + width - 1, y, x + width - 1, y + height - 1,shadowColor);
        }
    }
    else
    {
		g->drawLine(x, y + 1, x + width, y + 1, lColor);
		g->drawLine(x, y + 1, x, y + height - 2, lColor);
		g->drawLine(x + width + 1, y + 1, x + width + 1, y + height - 2, lColor);
    }
    g->drawLine(x + width, y, x + width, y + height - 1,shadowColor);
}

void SPClassicSkin::drawTabBar(
    SPGraphicsContext* g,
    SPTabBarElement* tabBar,
    int x,
    int y,
    int width,
    int height
)
{
    SPColor lColor = this->m_lightColor;
    SPColor shadowColor = this->m_shadowColor;
    SPColor bgColor = tabBar->getBackgroundColor();
    SPColor* tintColor = tabBar->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        lColor = lColor.tint(*tintColor);
        shadowColor = tintColor->lighten(-0);
    }
	if (tabBar->getColorScheme() == SP_COLOR_SCHEME_DARK) {
		bgColor = bgColor.lighten(2);
		shadowColor = shadowColor.lighten(-0.2);
	}
    SPGradient gradient(
        bgColor.lighten(0.1), bgColor.lighten(-0.1),
        0
        );
    g->drawLinearGradient(sp_rectangle {x, y, width, height}, gradient);
    if (this->m_glossy) {
    	SPGradient gradient2(
			bgColor.lighten(0.2), bgColor.lighten(0),
			0
		);
    	g->drawLinearGradient(sp_rectangle {x, y + 1, width, height / 2}, gradient2);
    }
    g->drawLine(x, y, x + width, y,shadowColor);
    g->drawLine(x, y + 1, x + width, y + 1, lColor);
    g->drawLine(x, y + height - 1, x + width, y + height - 1, shadowColor);
}

void SPClassicSkin::drawTreeItem(SPGraphicsContext* g, SPTreeViewElement *treeView, SPTreeItem* item, int itemHeight, int x, int y, int width, int height)
{
    if (item->isSelected()) {
        g->fillRectangle(x, y, treeView->getWidth(), itemHeight, SPColor(166, 218, 251, 255));
    }
    if (item->isHighlighted()) {
        g->fillRectangle(x, y, treeView->getWidth(), itemHeight, SPColor(166, 218, 251, 128));
    }
}

SPClassicSkin::SPClassicSkin() {
}
