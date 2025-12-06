#include "SPBoxElement.h"

#include "SPElement.h"
#include "SPNode.h"

namespace spider {
SPBoxElement::SPBoxElement()
 : SPElement()
{
    //ctor
}

SPBoxElement::SPBoxElement(SPElement *parent)
 : SPElement(parent)
{

}
SPBoxElement::~SPBoxElement()
{
    //dtor
}
/**
 Box Element
**/
void SPBoxElement::pack() {
	vector<SPNode *> *nodes = this->getChildNodes();
    if (this->getChildNodes()->size() < 1) {
        return;
    }
	SPNode *elm = (SPNode *)static_cast<spider::SPNode *>(*this->getChildNodes()->begin());
	SPElement *child = (SPElement *)elm;
	child->setX(0);
	child->setY(0);
	child->setWidth(this->getWidth());
	child->setHeight(this->getHeight());
	child->pack();

};
}
