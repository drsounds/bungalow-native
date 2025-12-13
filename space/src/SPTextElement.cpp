#include "SPTextElement.h"

#include "SPElement.h"
#include "SPGraphicsContext.h"
#include "SPFontStyle.h"
#include "SPColor.h"

namespace space {
SPTextElement::SPTextElement(SPElement *parent)
 : SPElement(parent)
{
	this->setTagName("text");
    //ctor
}
void SPTextElement::pack() {
    SPElement::pack();
	this->resizeToText(false, true);
}
void SPTextElement::paint(int x, int y, SPGraphicsContext *c)  {
    SPColor fgcolor = this->getColorAttribute("fgcolor", this->getForegroundColor());
    SPFontStyle fontStyle = this->getFontStyle();
    c->drawString(this->m_innerText, fontStyle, fgcolor, x ,y , this->getWidth(), this->getHeight());
}
SPTextElement::~SPTextElement()
{
    //dtor
}
}
