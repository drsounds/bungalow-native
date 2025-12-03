#include "WindowElement.h"

#include <iostream>

#include "GraphicsContext.h"

#include "Element.h"
#include "MainElement.h"
#include "../include/Spider.h"
#include "Element.h"

namespace spider
{
    class Spider;

    WindowElement::WindowElement(Spider *spider)
    {
        this->m_spider = spider;
    }

    void WindowElement::draw(GraphicsContext *gc, int x, int y) {
        std::vector<Node *> *elements = this->getChildNodes();
        for (auto node : *elements) {
            auto *elm = dynamic_cast<Element *>(node);
            if (elm->isVisible())
                elm->draw(0, 0, gc);
        }
    }
    void WindowElement::navigate(const string& uri) {
        this->dispatchEvent("navigate", nullptr, this);
    }
    void WindowElement::pack() {

        auto gc = this->createGraphics();

        int width = gc->getWidth();
        int height = gc->getHeight();
        for (auto & it : *this->getChildNodes()) {
            auto *elm = dynamic_cast<Element *>(it);
            elm->setX(0);
            elm->setY(0);
            elm->setWidth(width);
            elm->setHeight(height);
            elm->pack();
        }
    }
}
