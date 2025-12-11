#include "SPSplitterElement.h"

#include "SPElement.h"
#include "SPColor.h"

namespace space {
SPSplitterElement::SPSplitterElement(SPElement *parent)
 : SPElement(parent)
{
    //ctor
    this->setWidth(1);
    this->setBackgroundColor(SPColor(127, 127, 127, 255));
}

SPSplitterElement::~SPSplitterElement()
{
    //dtor
}
}
