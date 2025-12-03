#include "TextElement.h"

namespace spider {
TextElement::TextElement(Element *parent)
 : Element(parent)
{
    //ctor
}
void TextElement::draw(int x, int y, GraphicsContext *g) {
    Color fgcolor = this->getColorAttribute("fgcolor", Color(255, 255, 255, 0));
    FontStyle fontStyle = this->getFontStyle();
    g->drawString(this->data, fontStyle, fgcolor, x ,y , this->getWidth(), this->getHeight());
}
TextElement::~TextElement()
{
    //dtor
}
}
