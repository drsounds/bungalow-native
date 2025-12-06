#include "SPInputElement.h"
namespace spider {
SPInputElement::SPInputElement()
{
    //ctor
}

SPInputElement::~SPInputElement()
{

}
SPInputElement::SPInputElement(Element *parent)
    : Element(parent) {

}

void SPInputElement::draw(int x, int y, GraphicsContext *g) {
    Element::draw(x, y, g);
    g->drawInputElement(this, x, y, this->getWidth(), this->getHeight());
}
}
