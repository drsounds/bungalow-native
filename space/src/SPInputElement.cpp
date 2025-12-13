#include "SPInputElement.h"
namespace space {
SPInputElement::SPInputElement()
{
    //ctor
}

SPInputElement::~SPInputElement()
{

}
SPInputElement::SPInputElement(SPElement *parent)
    : SPElement(parent) {
	this->tagName = "input";
}

void SPInputElement::draw(int x, int y, SPGraphicsContext *g) {
    SPElement::draw(x, y, g);
    g->drawInputElement(this, x, y, this->getWidth(), this->getHeight());
}
}
