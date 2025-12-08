#include "SPSplitterElement.h"

#include "SPElement.h"
#include "SPColor.h"

namespace space {
SPSplitterElement::SPSplitterElement(SPElement *parent)
 : SPElement(parent)
{
    //ctor
    this->setIntegerAttribute("width", 1);
    this->setColorAttribute("bgcolor", SPColor(255, 255, 255, 1));
}

SPSplitterElement::~SPSplitterElement()
{
    //dtor
}
}
