#include "SPButtonElement.h"
#include "SPGraphicsContext.h"
#include "SPColor.h"
void spider::SPButtonElement::draw(int x, int y, SPGraphicsContext *c)
{
    if (this->absoluteBounds == nullptr)
    this->absoluteBounds = new sp_rectangle;

    this->absoluteBounds->x = x + this->getX();
    this->absoluteBounds->y = y + this->getY();
    this->absoluteBounds->width = this->getWidth();
    this->absoluteBounds->height = this->getHeight();

    SPColor bgColor = this->getColorAttribute("bgcolor", SPColor(0, 0, 0, 1));
    SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 1));
    int fontSize = this->getIntegerAttribute("size", 12);
    string fontFamily = this->getStringAttribute("font", "MS Sans Serif");
	c->fillRectangle(this->absoluteBounds->x, this->absoluteBounds->y, width, height, bgColor);

    if(!this->getInnerText().empty()) {
        spider::SPFontStyle fontStyle = SPFontStyle(fontFamily, fontSize, false, false, false);
		string text = this->getInnerText();
		spider::sp_rectangle tSize = c->measureString(text, fontStyle);
		int x = (this->getWidth() / 2) - (tSize.width / 2) + this->absoluteBounds->x;
		int y = (this->getHeight() / 2) - (tSize.height / 2) + this->absoluteBounds->y;

		c->drawString(text,fontStyle, fgColor, x, y, this->getWidth(), tSize.height);
	}
}
