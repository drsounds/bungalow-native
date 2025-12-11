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
    this->colors = new std::map<string, pixel *>;
    this->images = new std::map<string, SPImage *>;
    this->slices = new std::map<string, slice *>;
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

void SPSkin::drawTabBar(SPGraphicsContext* sp_graphics_context, SPTabBarElement* sp_tab_bar_element, int x, int y, int width, int height, const SPColor&, SPGraphicsContext*, int mode, SPColor* tintColor)
{
    SPColor line = SPColor(127, 127, 127, 1);
    sp_graphics_context->drawLine(x, y + height - 1, x + width, y + height - 1, line);
}

void SPSkin::drawTabBarTab(bool active, int x, int y, int width, int _height, const SPColor& sp_color, const SPColor& bg_color, SPGraphicsContext* sp_graphics_context, int mode, SPColor* tintColor)
{
    SPColor line = SPColor(127, 127, 127, 1);
    sp_graphics_context->drawLine(x, y + _height - 1, x + width, y + _height - 1, line);
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

void SPSkin::drawTableHeader(SPGraphicsContext* g, SPTableElement *table, int x, int y, int width, int height, SPColor *tintColor)
{

}

void SPSkin::drawTreeItem(SPGraphicsContext* g, int itemHeight, SPTreeViewElement* treeView, SPTreeItem* item, int x, int y, int width, int height, int mode, SPColor* tintColor)
{

}


bool SPSkin::drawElement(SPGraphicsContext* gc, SPElement*, const string& state, const sp_rectangle& bounds,
    SPColor* tintColor, short mode)
{
    return true;
}

void SPSkin::drawTableRow(SPGraphicsContext* g, SPTableElement* table, int i, int x, int y, int width, int height,
                          int row, SPColor* tintColor)
{
}

SPSkin::~SPSkin()
{
    //dtor
}
}
