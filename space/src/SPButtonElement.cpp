#include "SPButtonElement.h"
#include "SPGraphicsContext.h"
#include "SPColor.h"
#include "SPSkin.h"
#include "SPTextElement.h"

/**
 *
 * @param parent
 */
space::SPButtonElement::SPButtonElement(SPElement *parent) : SPElement(parent) {
	 this->tagName = "button";
}


void space::SPButtonElement::pack() {
	SPElement::pack();
	this->resizeToText(false, true);

}

void space::SPButtonElement::paint(int x, int y, SPGraphicsContext *c)
{
    if (this->absoluteBounds == nullptr)
    this->absoluteBounds = new sp_rectangle;

    this->absoluteBounds->x = x + this->getX();
    this->absoluteBounds->y = y + this->getY();
    this->absoluteBounds->width = this->getWidth();
    this->absoluteBounds->height = this->getHeight();

	string strClass;
	switch (this->getState()) {
	case SP_STATE_ACTIVE:
		strClass = "active";
		break;
	case SP_STATE_HOVER:
		strClass = "hover";
	}

	this->getSkin()->drawElement(c, this, strClass, *this->absoluteBounds);

    if(!this->getInnerText().empty()) {
        space::SPFontStyle fontStyle = this->getFontStyle();
		string text = this->getInnerText();
		space::sp_rectangle tSize = c->measureString(text, fontStyle);
		int x = (this->getWidth() / 2) - (tSize.width / 2) + this->absoluteBounds->x;
		int y = (this->getHeight() / 2) - (tSize.height / 2) + this->absoluteBounds->y;

		c->drawString(text,fontStyle, getForegroundColor(), x, y, tSize.width, tSize.height);
	}
}
