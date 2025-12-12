//
// Created by Alexander Forselius on 2025-12-11.
//

#include "SPClassicSkin.h"

#include "SPGraphicsContext.h"
#include "libspace.h"
#include "SPAppHeaderElement.h"
#include "SPButtonElement.h"
#include "SPColor.h"

using namespace space;

bool SPClassicSkin::drawElement(SPGraphicsContext* g, SPElement *elm, const string& state, const sp_rectangle& bounds)
{
    bool result = false;
    SPColor bgColor = elm->getBackgroundColor();
    SPColor fgColor = elm->getForegroundColor();
    SPColor *tintColor = elm->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        fgColor = fgColor.tint(*tintColor);
    }
    if (elm->getType() == "button")
    {
        result = true;
    	SPColor bgColor = elm->getBackgroundColor();
    	if (tintColor != nullptr) {
    		bgColor = bgColor.tint(*tintColor);
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
    	if (this->glossy && state != "active") {
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
			bgColor.lighten(-0.2)
    	);
    }
    if (elm->getType() == "tabbar")
    {
        result = true;
        auto *tabBar = dynamic_cast<SPTabBarElement *>(elm);
        SPGradient gradient(
            bgColor.lighten(-0.8), bgColor.lighten(-0.9),
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
    }
    if (elm->getType() == "table")
    {

    }
    if (elm->getType() == "appheader")
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
    	if (this->glossy && state != "active") {
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
    	if (this->glossy && state != "active") {
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
    SPColor color = this->getColor("table::nth-child(2n).background.color", "");
    SPColor *tintColor = table->getTintColor();
    if (tintColor != nullptr)
    {
        color = color.tint(*tintColor);
    }
    if (i % 2 != 1) {
        g->fillRectangle(x, y, width, 18, color);
    }
}

void SPClassicSkin::drawTableHeader(SPGraphicsContext* g, SPTableElement *table, int x, int y, int width, int height)
{
    SPColor bgColor = table->getBackgroundColor();
    SPColor *tintColor = table->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
    }
    SPGradient gradient(
        bgColor.lighten(-0.8),
        bgColor.lighten(-0.9),
        0
    );
    g->drawLinearGradient(sp_rectangle { x, y, width, height }, gradient);
}

void SPClassicSkin::drawTabBarTab(SPGraphicsContext* g, SPTabBarElement *tabBar, SPTab* tab, int index, bool active, int x, int y, int width, int height)
{
    SPColor bgColor = tabBar->getBackgroundColor();
    SPColor lColor = this->m_lightColor;
    SPColor shadowColor = this->m_shadowColor;
    SPColor* tintColor = tabBar->getTintColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        shadowColor = shadowColor.tint(*tintColor);
        lColor = lColor.tint(*tintColor);
    }
    if (active)
    {
        g->fillRectangle(x, y + 1, width, height - 1, bgColor);
        if (index > 0)
        {
            g->drawLine(x, y, x, y + height - 1,shadowColor);
        }
    }
    else
    {
        SPGradient gradient(bgColor.lighten(0.5), bgColor, 0);
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
        shadowColor = shadowColor.tint(*tintColor);
    }
    SPGradient gradient(
        bgColor.lighten(0.1), bgColor.lighten(-0.1),
        0
        );
    g->drawLinearGradient(sp_rectangle {x, y, width, height}, gradient);
    if (this->glossy) {
    	SPGradient gradient2(
			bgColor.lighten(0.2), bgColor.lighten(0),
			0
		);
    	g->drawLinearGradient(sp_rectangle {x, y + 1, width, height / 2}, gradient2);
    }
    //g->drawLine(x, y, x + width, y,shadowColor);
    g->drawLine(x, y + height - 1, x + width, y + height - 1,shadowColor);
}

void SPClassicSkin::drawTreeItem(SPGraphicsContext* g, SPTreeViewElement *treeView, SPTreeItem* item, int itemHeight, int x, int y, int width, int height)
{
    if (item->isSelected()) {
#if spacify2009
        g->fillRectangle(x, y, this->getWidth(), itemHeight, this->getColor("treeitem::selected.background.color", ""));
#else
        g->fillRectangle(x, y, 5, itemHeight, treeView->getColorAttribute("highlight", SPColor(0, 127, 255, 255)));
#endif
    }
    if (item->isHighlighted()) {
        g->fillRectangle(x, y , treeView->getWidth(), itemHeight, this->getColor("treeitem::focus.background.color", ""));

    }
}
