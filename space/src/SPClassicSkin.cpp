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

bool SPClassicSkin::drawElement(SPGraphicsContext* g, SPElement *elm, const string& state, const sp_rectangle& bounds, SPColor *tintColor, short mode)
{
    bool result = false;
    SPColor bgColor = elm->getBackgroundColor();
    SPColor fgColor = elm->getForegroundColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        fgColor = fgColor.tint(*tintColor);
    }
    if (elm->getType() == "button")
    {
        result = true;
        auto *button = dynamic_cast<SPButtonElement *>(elm);
        SPGradient gradient(
            bgColor.lighten(-0.8), bgColor.lighten(-0.9),
            0
        );
        if (state == "active")
        {
            gradient = SPGradient(SPColor(0, 0, 0, 1), SPColor(10, 10, 10, 0), 0);
        }
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
    if (elm->getType() == "tabbar")
    {
        result = true;
        auto *tabBar = dynamic_cast<SPTabBarElement *>(elm);
        SPGradient gradient(
            bgColor.lighten(-0.8), bgColor.lighten(-0.9),
            0
        );
        if (state == "active")
        {
            gradient = SPGradient(SPColor(0, 0, 0, 1), SPColor(10, 10, 10, 0), 0);
        }
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
        auto *appHeader = dynamic_cast<SPAppHeaderElement *>(elm);
        auto width = appHeader->getWidth();
        auto height = appHeader->getHeight();
        SPGradient gradient(
            bgColor.lighten(0.5), bgColor.lighten(0),
            0
        );
        if (state == "active")
        {
            gradient = SPGradient(SPColor(0, 0, 0, 1), SPColor(10, 10, 10, 0), 0);
        }
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

void SPClassicSkin::drawTableRow(SPGraphicsContext *g, SPTableElement *table, int i, int x, int y, int width, int height, int row, SPColor *tintColor)
{
    SPColor color = this->getColor("table::nth-child(2n).background.color", "");
    if (tintColor != nullptr)
    {
        color = color.tint(*tintColor);
    }
    if (i % 2 != 1) {
        g->fillRectangle(x, y, width, 18, color);
    }
}

void SPClassicSkin::drawTableHeader(SPGraphicsContext* g, SPTableElement *table, int x, int y, int width, int height, SPColor *tintColor)
{
    SPColor bgColor = table->getBackgroundColor();
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

void SPClassicSkin::drawTabBarTab(bool active, int x, int y, int width, int height, const SPColor& sp_color,
    const SPColor& bg_color, SPGraphicsContext* g, int mode, SPColor *tintColor)
{
    SPColor bgColor = bg_color;
    SPColor fgColor = sp_color;
    SPColor shadowColor = SPColor(80, 80, 80, 255);
    SPColor lColor = SPColor(128, 128, 128, 255);
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        shadowColor = shadowColor.tint(*tintColor);
        lColor = lColor.tint(*tintColor);
    }
    if (active)
    {
        g->fillRectangle(x, y, width, height + 1, bgColor);
    }
    else
    {
        SPGradient gradient(bgColor.lighten(0.5), bgColor, 0);
        g->drawLinearGradient({x, y, width, height }, gradient);
    }
    g->drawLine(x, y, x + width, y, shadowColor);
    g->drawLine(x + width, y + 1, x + width, y + height, lColor);
    g->drawLine(x + width - 1, y + 1, x + width - 1, y + height, shadowColor);
}

void SPClassicSkin::drawTabBar(
    SPGraphicsContext* g,
    SPTabBarElement* tabbar,
    int x,
    int y,
    int width,
    int height,
    const SPColor& sp_color,
    SPGraphicsContext* sp_graphics_context1,
    int mode,
    SPColor *tintColor
)
{
    SPColor shadowColor = SPColor(80, 80, 80, 255);
    SPColor lColor = SPColor(128, 128, 128, 255);
    SPColor bgColor = tabbar->getBackgroundColor();
    if (tintColor != nullptr)
    {
        bgColor = bgColor.tint(*tintColor);
        lColor = lColor.tint(*tintColor);
        shadowColor = shadowColor.tint(*tintColor);
    }
    SPGradient gradient(
        bgColor.lighten(-0.1), bgColor.lighten(-0.3),
        0
    );
    g->drawLinearGradient(sp_rectangle {x, y, width, height}, gradient);
    g->drawLine(x, y, x + width, y,shadowColor);
    g->drawLine(x, y + 1, x + width, y + 1, lColor);
    g->drawLine(x, y + height, x + width, y + height,shadowColor);
}

void SPClassicSkin::drawTreeItem(SPGraphicsContext* g, int itemHeight, SPTreeViewElement *treeView, SPTreeItem* item, int x, int y, int width, int height, int mode, SPColor *tintColor)
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
