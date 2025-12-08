#include "SPContainerViewElement.h"
namespace space {
    SPContainerViewElement::SPContainerViewElement(SPElement *parent)
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
