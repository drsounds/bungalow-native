#include "SPAppHeaderElement.h"

#include "SPElement.h"
#include "SPColor.h"

namespace space {
SPAppHeaderElement::SPAppHeaderElement(SPElement *parent) : SPHBoxElement(parent)
{
    this->setColorAttribute("bgcolor", SPColor(127, 127, 127, 255));
    //ctor
}

SPAppHeaderElement::~SPAppHeaderElement()
{
    //dtor
}

}
