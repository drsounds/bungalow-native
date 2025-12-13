#include "SPViewElement.h"
#include <string>
#include <iostream>

using namespace std;

namespace space {
SPViewElement::SPViewElement()
 : SPVBoxElement::SPVBoxElement()
{

    //ctor
}
void SPViewElement::scroll(int scrollX, int scrollY, int mouseX, int mouseY) {
    if (this->clipView) {
        this->scrollX += x;
        this->scrollY += y;
        this->invalidate();
    }
}
void SPViewElement::request(std::string uri) {

}

std::string SPViewElement::loadXml(const std::string& view) {

}

void SPViewElement::pack() {
    SPVBoxElement::pack();
}

SPViewElement::SPViewElement(SPElement *parent)
 : SPVBoxElement::SPVBoxElement(parent)
{
    this->clipView = true;
    //ctor
}
void SPViewElement::navigate(const string& uri) {

}
SPViewElement::~SPViewElement()
{
    //dtor
}
}
