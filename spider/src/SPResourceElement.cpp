#include "SPResourceElement.h"
#include "SPGraphicsContext.h"
#include "SPFontStyle.h"
#include "SPResource.h"
#include <regex>

namespace spider {
    SPResourceElement::SPResourceElement(SPResource *resource, SPElement *parent)
     : SPElement(parent)
    {
        //ctor
        this->resource = resource;
    }
    void SPResourceElement::draw(int x, int y, SPGraphicsContext *g) {
        SPFontStyle font = this->getFontStyle();
        SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 1));
        SPColor bgColor = this->getColorAttribute("bgcolor", SPColor(0, 0, 0, 1));
        if (this->resource != NULL) {

            // draw title
            string name = this->resource->getName();
            string title = name;
            sp_rectangle txtSize = g->measureString(title, font);
            int top = (this->getHeight() / 2) - (txtSize.height / 2);
            g->drawString(title, font, fgColor, x + 10, top, this->getWidth(), this->getHeight());

            // draw separator
            g->drawLine(x, this->getHeight()-1 + y, this->getWidth() + x, this->getHeight()-1 + y, fgColor);
        }
    }
    SPResourceElement::~SPResourceElement()
    {
        //dtor
    }
}
