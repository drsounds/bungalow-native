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
