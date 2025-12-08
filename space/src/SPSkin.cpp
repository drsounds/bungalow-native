#include "SPSkin.h"

#include "SPImage.h"
#include "SPColor.h"
#include "SPElement.h"

#include <iostream>

#include "SPAppHeaderElement.h"
#include "SPButtonElement.h"
#include "SPGraphicsContext.h"
#include "SPTabBarElement.h"
#include "SPTableElement.h"

namespace space {
SPSkin::SPSkin()
{
    //ctor
}

bool SPSkin::drawElement(SPGraphicsContext* g, SPElement *elm, const string& state, const sp_rectangle& bounds, const SPColor& tint, short mode)
{
    bool result = false;
    SPColor bgColor = mode == SP_MODE_DARK ? SPColor(20, 20, 20, 255) : SPColor(230, 230, 230, 255);
    SPColor fgColor = mode == SP_MODE_DARK ? SPColor(220, 220, 220, 255) : SPColor(30, 30, 30, 255);
    if (elm->getType() == "button")
    {
        result = true;
        auto *button = dynamic_cast<SPButtonElement *>(elm);
        bgColor = SPColor(100, 100, 100, 255);
        fgColor = SPColor(0, 0, 0, 255);
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
        bgColor = SPColor(100, 100, 100, 255);
        fgColor = SPColor(0, 0, 0, 255);
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
        bgColor = SPColor(100, 100, 100, 255);
        fgColor = SPColor(0, 0, 0, 255);
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
        bgColor = SPColor(88, 88, 88, 255);
        fgColor = SPColor(0, 0, 0, 255);
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

void SPSkin::drawTableRow(SPGraphicsContext *g, SPTableElement *table, int i, int x, int y, int width, int height, int row)
{
    if (i % 2 != 1) {
        g->fillRectangle(x, y, width, 18, this->getColor("table::nth-child(2n).background.color", ""));

    }
}

void SPSkin::drawTableHeader(SPGraphicsContext* g, SPTableElement *table, int x, int y, int width, int height)
{
    SPColor bgColor = table->getBackgroundColor();
    SPGradient gradient(
        bgColor.lighten(-0.8),
        bgColor.lighten(-0.9),
        0
    );
    g->drawLinearGradient(sp_rectangle { x, y, width, height }, gradient);
}

void SPSkin::drawTabBarTab(bool active, int x, int y, int width, int height, const SPColor& sp_color,
    const SPColor& bg_color, SPGraphicsContext* g)
{

    if (active)
    {
        g->fillRectangle(x, y, width, height + 1, bg_color);
    }
    else
    {
        SPGradient gradient(bg_color.lighten(0.5), bg_color, 0);
        g->drawLinearGradient({x, y, width, height }, gradient);
    }
    g->drawLine(x, y, x + width, y, SPColor(80, 80, 80, 255));
    g->drawLine(x + width, y + 1, x + width, y + height, SPColor(128, 128, 128, 255));
    g->drawLine(x + width - 1, y + 1, x + width - 1, y + height, SPColor(0, 0, 0, 255));
}

void SPSkin::drawTabBar(SPGraphicsContext* g, SPTabBarElement* tabbar, int x, int y, int width,
    int height, const SPColor& sp_color, SPGraphicsContext* sp_graphics_context1)
{
    SPColor bgColor = SPColor(127, 127, 127, 255);
    SPGradient gradient(
        bgColor.lighten(-0.1), bgColor.lighten(-0.3),
        0
    );
    g->drawLinearGradient(sp_rectangle {x, y, width, height}, gradient);
    g->drawLine(x, y, x + width, y, SPColor(80, 80, 80, 255));
    g->drawLine(x, y + 1, x + width, y + 1, SPColor(128, 128, 128, 255));
    g->drawLine(x, y + height, x + width, y + height, SPColor(0, 0, 0, 255));
}

void SPSkin::drawTreeItem(SPGraphicsContext* g, int itemHeight, SPTreeViewElement *treeView, SPTreeItem* item, int x, int y, int width, int height)
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
    SPColor color =  this->getColor("treeview.foreground.color", "");
    if(item->isSelected())
    {
        if (false)
        {
            color = treeView->getColorAttribute("highlight", SPColor(0, 0, 255, 1));
        }
        else
        {
            color = this->getColor("treeitem::selected.foreground.color", "");
        }
    }



}

slice::slice(SPImage *image, int x1, int y1, int x2, int y2, int leftBorder, int topBorder, int rightBorder, int bottomBorder) {
    this->image = image;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->leftBorder = leftBorder;
    this->topBorder = topBorder;
    this->rightBorder = rightBorder;
    this->bottomBorder = bottomBorder;
}
    
SPSkin::SPSkin(const string& bitmap) {
    this->colors = new std::map<string, pixel *>;
    this->images = new std::map<string, SPImage *>;
    this->slices = new std::map<string, slice *>;
    cout << bitmap << "\r\n";
    SPImage *image = new SPImage(bitmap);
    cout << "Sizeof pixels: " << sizeof(image->pixels) << "\r\n";
    this->image = image;
    cout << "Sizeof pixels: " << sizeof(image->pixels) << "\r\n";
    this->colors->insert(pair<string, pixel *>("body.background.color", this->image->getPixelPtr(0, 0)));

    (*this->colors)["body.foreground.color"] = this->image->getPixelPtr(1, 0);
    (*this->colors)["::selected.background.color"] = this->image->getPixelPtr(7, 0);
    (*this->colors)["::selected.foreground.color"] = this->image->getPixelPtr(8, 0);
    (*this->slices)["#header.background.image"] = new slice(image, 214, 0, 27, 56, 1, 0, 0, 0);
    (*this->slices)["tab.background.image::active"] = new slice(image, 0, 11, 32, 23, 1, 1, 1, 1);
    (*this->slices)["tabbar.background.image"] = new slice(image, 97, 1, 1, 22, 0, 0, 0, 0);
    (*this->slices)["button.background.image"] = new slice(image, 128, 1, 71, 19, 3, 13, 13, 3);
    (*this->slices)["table::columnheader.background.image"] = new slice(image, 200, 63, 18, 18, 0, 0, 0, 0);
    (*this->colors)["table::nth-child(2n).background.color"] = this->image->getPixelPtr(22, 0);
    (*this->colors)["treeitem::selected.background.color"] = this->image->getPixelPtr(6, 0);
    (*this->colors)["treeitem::selected.foreground.color"] = this->image->getPixelPtr(7, 0);
    (*this->colors)["treeview.foreground.color"] = this->image->getPixelPtr(1, 0);
    (*this->colors)["treeitem::focus.foreground.color"] = this->image->getPixelPtr(2, 0);
    (*this->colors)["treeview.background.color"] = this->image->getPixelPtr(3, 0);
  //  (*this->images)["button.background.image::active"] = this->image->sliceImage(128, 21, 71, 19, 3, 13, 13, 3);
}
bool SPSkin::hasColor(string selector) {
    if(this->colors->find(selector) != this->colors->end()) {
        return true;
    }
    return false;
}

bool SPSkin::hasImage(string selector) {
    if(this->images->find(selector) != this->images->end()) {
        return true;
    }
    return false;
}
SPColor SPSkin::getColor(string selector, string def) {
    if (!this->hasColor(selector)) {
        return SPColor(255, 255, 255, 255);
    }
    return *space_pixel_to_colour((*this->colors)[selector]);
}
SPImage *SPSkin::getImage(string selector, string def) {
    if (!this->hasImage(selector)) {
        return NULL;
    }
    return (*this->images)[selector];
}
SPSkin::~SPSkin()
{
    //dtor
}
}
