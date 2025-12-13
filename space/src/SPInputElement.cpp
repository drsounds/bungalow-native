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

void SPInputElement::paint(int x, int y, SPGraphicsContext *g) {
    SPElement::paint(x, y, g);
    g->drawInputElement(this, x, y, this->getWidth(), this->getHeight());
}
}
