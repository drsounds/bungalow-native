#include "SPAppHeaderElement.h"
namespace spider {
SPAppHeaderElement::SPAppHeaderElement(SPElement *parent) : SPHBoxElement(parent)
{
   this->generateAndSetDefaultGradient();
    //ctor
}

SPAppHeaderElement::~SPAppHeaderElement()
{
    //dtor
}

}
