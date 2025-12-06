#include "SPFlowElement.h"
namespace spider {
SPFlowElement::SPFlowElement()
 : Element::Element()
{
    //ctor
}

SPFlowElement::SPFlowElement(Element *elm)
 : Element::Element(elm)
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
    for(std::vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
        Element *child = (Element *)*it;
         if (!child->isVisible())
            continue;
        child->setY(top);
        child->setWidth(this->getWidth());
        child->pack();
        top += child->getHeight();
    }
}
}
