#include "SPInputElement.h"
namespace spider {
SPInputElement::SPInputElement()
{
    //ctor
}

SPInputElement::~SPInputElement()
{

}
SPInputElement::SPInputElement(SPElement *parent)
    : SPElement(parent) {

}

void SPInputElement::draw(int x, int y, SPGraphicsContext *g) {
    SPElement::draw(x, y, g);
    g->drawInputElement(this, x, y, this->getWidth(), this->getHeight());
}
}
