#include "GraphicsContext.h"
namespace spider {
    void GraphicsContext::setOrigo(const int& x, const int& y) {
    }
    GraphicsContext::GraphicsContext(WindowElement *window) {
        this->window = window;
    }
    void GraphicsContext::drawImageSlices(map<string, slice *> *slices, string selector, int left, int top, int width, int height)
    {
        if(slices->find(selector) != slices->end()) {
            slice *slice = (*slices)[selector];
            this->drawImagePart(slice->image, left, top, width, height, slice->x1, slice->y1, slice->x2, slice->y2);
        }
    }
}
