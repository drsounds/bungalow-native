#include "SPImageElement.h"
namespace spider {
SPImageElement::SPImageElement(Element *parent)
 : Element(parent)
{
    //ctor
}
void SPImageElement::draw(int x, int y, GraphicsContext *g) {
    //g->drawImage(NULL, x, y, this->getWidth(), this->getHeight());
}
SPImageElement::~SPImageElement()
{
    //dtor
}
}
