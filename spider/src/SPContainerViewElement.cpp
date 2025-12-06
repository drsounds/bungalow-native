#include "SPContainerViewElement.h"
namespace spider {
    SPContainerViewElement::SPContainerViewElement(Element *parent)
    : SPViewElement(parent)
    {
        //ctor
        this->clipView = true;
    }

    SPContainerViewElement::SPContainerViewElement()
    : SPViewElement()
    {
        //ctor
        this->clipView = true;
    }

    SPContainerViewElement::~SPContainerViewElement()
    {
        //dtor
    }
}
