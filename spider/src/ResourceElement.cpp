#include "ResourceElement.h"
#include "GraphicsContext.h"
#include "FontStyle.h"
#include "Resource.h"
#include <regex>

namespace spider {
    ResourceElement::ResourceElement(Resource *resource, Element *parent)
     : Element(parent)
    {
        //ctor
        this->resource = resource;
    }
    void ResourceElement::draw(int x, int y, GraphicsContext *g) {
        FontStyle font = this->getFontStyle();
        Color fgColor = this->getColorAttribute("fgcolor", Color(255, 255, 255, 1));
        Color bgColor = this->getColorAttribute("bgcolor", Color(0, 0, 0, 1));
        if (this->resource != NULL) {

            // draw title
            string name = this->resource->getName();
            string title = name;
            rectangle txtSize = g->measureString(title, font);
            int top = (this->getHeight() / 2) - (txtSize.height / 2);
            g->drawString(title, font, fgColor, x + 10, top, this->getWidth(), this->getHeight());

            // draw separator
            g->drawLine(x, this->getHeight()-1 + y, this->getWidth() + x, this->getHeight()-1 + y, fgColor);
        }
    }
    ResourceElement::~ResourceElement()
    {
        //dtor
    }
}
