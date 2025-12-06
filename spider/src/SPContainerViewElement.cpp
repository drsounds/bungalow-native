#include "SPContainerViewElement.h"
namespace spider {
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
