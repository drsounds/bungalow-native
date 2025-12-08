#include "SPAppHeaderElement.h"
namespace space {
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
