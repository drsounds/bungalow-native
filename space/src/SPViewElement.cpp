#include "SPViewElement.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;

namespace space {
SPViewElement::SPViewElement() : SPVBoxElement() {
	this->setTagName("view");
}
SPViewElement::SPViewElement(SPElement *parent)
 : SPVBoxElement::SPVBoxElement(parent)
{
	this->setTagName("view");
    this->clipView = true;
    //ctor
}
void SPViewElement::scroll(int scrollX, int scrollY, int mouseX, int mouseY) {
    if (this->clipView) {
        this->scrollX += x;
        this->scrollY += y;
        this->invalidate();
    }
}
void SPViewElement::pack() {
    SPVBoxElement::pack();
}
void SPViewElement::navigate(const string& uri) {

}

bool SPViewElement::acceptsUri(const string &uri) {
	return true;
}

SPViewElement::~SPViewElement()
{
    //dtor
}
}
