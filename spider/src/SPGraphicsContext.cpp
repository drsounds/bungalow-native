#include "SPGraphicsContext.h"

#include "SPSkin.h"

namespace spider {
    void SPGraphicsContext::setOrigo(const int& x, const int& y) {
    }

    SPGraphicsContext::SPGraphicsContext()
    {
        this->m_spider = nullptr;
    }

    SPGraphicsContext::SPGraphicsContext(Spider *spider) : SPGraphicsContext()
    {
        this->m_spider = spider;
    }

    void SPGraphicsContext::drawImageSlices(map<string, slice *> *slices, string selector, int left, int top, int width, int height)
    {
        if(slices->find(selector) != slices->end()) {
            slice *slice = (*slices)[selector];
            this->drawImagePart(slice->image, left, top, width, height, slice->x1, slice->y1, slice->x2, slice->y2);
        }
    }
}
