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
	int width = this->getWidth();
	int height = this->getHeight();
    g->drawInputElement(this, x, y, width, height);
}
}
