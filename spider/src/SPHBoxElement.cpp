#include "SPHBoxElement.h"

#include <iostream>

namespace spider {
    SPHBoxElement::SPHBoxElement()
    {
        //ctor
    }

    void SPHBoxElement::pack() {
        int height = this->getHeight();
        int flexes = 0;
        int statics = 0;
        int leftWidth = 0;
        int rightWidth = 0;
        int side = -1;
        // First calculate count of flex
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if(child->getIntegerAttribute("flex", 0) > 0) {
                flexes++;
                side = 0;
            } else {
                if(side == 0)
                    side+=1;
                if(side > 1)
                    side = 1;
                statics++;
                if(side < 1)
                    leftWidth += child->getWidth();
                else if(side > 0)
                    rightWidth += child->getWidth();
            }
        }

        int flexWidth = flexes > 0 ? (this->getWidth() - leftWidth - rightWidth) / flexes : 0;
        float flex = 1;
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if(child->getIntegerAttribute("flex", 0 ) > 0) {
        //		child->setWidth((flex / flexes) * flexWidth);
            //	flex = (int)child->getAttribute("flex");
                child->setWidth((1 / flexes) * flexWidth);
            } else {
                statics++;
            }
            child->setWidth(child->getWidth());
        }

        // Now assign elements
        int left = 0;
        int right = 0;
        side = -1;
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if(child->getIntegerAttribute("flex", 0) > 0) {

                side = 0;
            } else {
                if(side == 0)
                    side = 1;
            }
            if(side < 0)
                child->setX(left + child->getMargins()->left + this->getPadding()->left	);
            else if(side == 0) {
                child->setX(leftWidth + child->getMargins()->left);

            }
            else if(side > 0) {
                child->setX(leftWidth + flexWidth + right -this->getPadding()->right *2 - this->getMargins()->right * 2);

            }
            child->setY(this->getPadding()->top + child->getMargins()->top);

            child->setHeight(this->getHeight() - (this->getPadding()->bottom * 2 + child->getMargins()->bottom * 2));
            cout << "SPHBoxElement height: " << this->getHeight() << endl;
            cout << "SPHBoxElement Child: " << child->getType() << " Height: " << this->getHeight() << endl;
            switch(side) {
                case -1:
                    left += child->getWidth();
                    break;
                case 0:
                    break;
                case 2:
                    right += child->getWidth();
                    break;
            }
        }



        // Pack child elements
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if (!child->isVisible())
                continue;
            child->pack();
        }

    };

}
