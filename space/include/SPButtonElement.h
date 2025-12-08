#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H
#include "SPElement.h"

string RGBToHex(int rNum, int gNum, int bNum);

namespace space {
	class SPColor;
	class SPGraphicsContext;
	class SPButtonElement : public SPElement {
	public:
        SPButtonElement(SPElement *parent) : SPElement(parent) {

	    }
		SPButtonElement();
		void draw(int x, int y, SPGraphicsContext *c);
		virtual string getType() {
            return "button";
		}
	};
}
#endif // BUTTONELEMENT_H
