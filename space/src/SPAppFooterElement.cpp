#include "SPAppFooterElement.h"

#include "SPElement.h"
#include "SPHBoxElement.h"

namespace space {
    SPAppFooterElement::SPAppFooterElement(SPElement *parent) : SPHBoxElement(parent)
    {
        this->setColorAttribute("bgcolor", SPColor(57, 57, 57, 255));
        //ctor
    }

    SPAppFooterElement::~SPAppFooterElement()
    {
        //dtor
    }

}
