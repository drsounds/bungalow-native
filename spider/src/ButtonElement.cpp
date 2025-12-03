#include "ButtonElement.h"
#include "GraphicsContext.h"
#include "Color.h"
void spider::ButtonElement::draw(int x, int y, GraphicsContext *c)
{
    if (this->absoluteBounds == nullptr)
    this->absoluteBounds = new rectangle;

    this->absoluteBounds->x = x + this->getX();
    this->absoluteBounds->y = y + this->getY();
    this->absoluteBounds->width = this->getWidth();
    this->absoluteBounds->height = this->getHeight();

    Color bgColor = this->getColorAttribute("bgcolor", Color(0, 0, 0, 1));
    Color fgColor = this->getColorAttribute("fgcolor", Color(255, 255, 255, 1));
    int fontSize = this->getIntegerAttribute("size", 12);
    string fontFamily = this->getStringAttribute("font", "MS Sans Serif");
	c->fillRectangle(this->absoluteBounds->x, this->absoluteBounds->y, width, height, bgColor);

    if(!this->getInnerText().empty()) {
        spider::FontStyle fontStyle = FontStyle(fontFamily, fontSize, false, false, false);
		string text = this->getInnerText();
		spider::rectangle tSize = c->measureString(text, fontStyle);
		int x = (this->getWidth() / 2) - (tSize.width / 2) + this->absoluteBounds->x;
		int y = (this->getHeight() / 2) - (tSize.height / 2) + this->absoluteBounds->y;

		c->drawString(text,fontStyle, fgColor, x, y, this->getWidth(), tSize.height);
	}
}
