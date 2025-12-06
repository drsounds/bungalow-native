#include "SPTextElement.h"

#include "SPElement.h"
#include "SPGraphicsContext.h"
#include "SPFontStyle.h"
#include "SPColor.h"

namespace spider {
SPTextElement::SPTextElement(SPElement *parent)
 : SPElement(parent)
{
    //ctor
}
void SPTextElement::draw(int x, int y, SPGraphicsContext *g) {
    SPColor fgcolor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 0));
    SPFontStyle fontStyle = this->getFontStyle();
    g->drawString(this->data, fontStyle, fgcolor, x ,y , this->getWidth(), this->getHeight());
}
SPTextElement::~SPTextElement()
{
    //dtor
}
}
