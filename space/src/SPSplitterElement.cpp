#include "SPSplitterElement.h"

#include "SPElement.h"
#include "SPColor.h"
#include "SPGraphicsContext.h"

namespace space {
SPSplitterElement::SPSplitterElement(SPElement *parent)
 : SPElement(parent)
{
    //ctor
    this->setWidth(1);
}
void SPSplitterElement::paint(int x, int y, int width, int height, SPGraphicsContext *c) {
	SPColor borderColor = this->getBackgroundColor();
	if (width <= 1) {
		width = 1;
		c->drawLine(x, y, x, y + height, borderColor);
		return;
	}
	if (height <= 1) {
		height = 1;
		c->drawLine(x, y, x + width, y, borderColor);
	}
}
SPSplitterElement::~SPSplitterElement()
{
    //dtor
}
}
