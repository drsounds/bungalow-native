#include "SPTextElement.h"

#include "Element.h"
#include "GraphicsContext.h"
#include "FontStyle.h"
#include "Color.h"

namespace spider {
SPTextElement::SPTextElement(Element *parent)
 : Element(parent)
{
    //ctor
}
void SPTextElement::draw(int x, int y, GraphicsContext *g) {
    Color fgcolor = this->getColorAttribute("fgcolor", Color(255, 255, 255, 0));
    FontStyle fontStyle = this->getFontStyle();
    g->drawString(this->data, fontStyle, fgcolor, x ,y , this->getWidth(), this->getHeight());
}
SPTextElement::~SPTextElement()
{
    //dtor
}
}
