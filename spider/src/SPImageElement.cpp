#include "SPImageElement.h"
namespace spider {
SPImageElement::SPImageElement(SPElement *parent)
 : SPElement(parent)
{
    //ctor
}
void SPImageElement::draw(int x, int y, SPGraphicsContext *g) {
    //g->drawImage(NULL, x, y, this->getWidth(), this->getHeight());
}
SPImageElement::~SPImageElement()
{
    //dtor
}
}
