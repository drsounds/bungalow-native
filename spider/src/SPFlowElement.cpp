#include "SPFlowElement.h"
namespace spider {
SPFlowElement::SPFlowElement()
 : SPElement::SPElement()
{
    //ctor
}

SPFlowElement::SPFlowElement(SPElement *elm)
 : SPElement::SPElement(elm)
{
    //ctor
}

SPFlowElement::~SPFlowElement()
{
    //dtor
}
void SPFlowElement::pack() {
    int top = 0;
    int left = 0;
    for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
        SPElement *child = (SPElement *)*it;
         if (!child->isVisible())
            continue;
        child->setY(top);
        child->setWidth(this->getWidth());
        child->pack();
        top += child->getHeight();
    }
}
}
