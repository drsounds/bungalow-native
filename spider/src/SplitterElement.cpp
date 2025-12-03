#include "SplitterElement.h"

#include "Element.h"
#include "Color.h"

namespace spider {
SplitterElement::SplitterElement(Element *parent)
 : Element(parent)
{
    //ctor
    this->setIntegerAttribute("width", 1);
    this->setColorAttribute("bgcolor", Color(255, 255, 255, 1));
}

SplitterElement::~SplitterElement()
{
    //dtor
}
}
