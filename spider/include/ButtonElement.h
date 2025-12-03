#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H
#include "Element.h"

string RGBToHex(int rNum, int gNum, int bNum);

namespace spider {
	class Color;
	class GraphicsContext;
	class ButtonElement : public Element {
	public:
        ButtonElement(Element *parent) : Element(parent) {

	    }
		ButtonElement();
		void draw(int x, int y, GraphicsContext *c);
		virtual string getType() {
            return "button";
		}
	};
}
#endif // BUTTONELEMENT_H
