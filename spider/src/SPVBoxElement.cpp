#include "SPVBoxElement.h"

#include <iostream>

namespace spider {
    SPVBoxElement::SPVBoxElement()
    {
    }

    SPVBoxElement::SPVBoxElement(SPWindowElement* parent) : SPBoxElement((SPElement *)parent)
    {
    }


    void spider::SPVBoxElement::pack() {
        int width = this->getWidth();
        int flexes = 0;
        int statics = 0;
        int topHeight = 0;
        int bottomHeight = 0;
        int side = -1;
        // First calculate count of flex
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {

            SPElement *child = static_cast<SPElement *>(*it);
            if (!child->isVisible())
                continue;
            if(child->getIntegerAttribute("flex", 0 ) > 0) {
                flexes++;
                side = 0;
            } else {
                if(side == 0)
                    side+=1;
                if(side > 1)
                    side = 1;
                statics++;
                if(side < 1)
                    topHeight += child->getHeight();
                else if(side > 0)
                    bottomHeight += child->getHeight();
            }
        }

        int flexHeight = flexes > 0 ?  (this->getHeight() - topHeight - bottomHeight) / flexes : 0;
        float flex = 1;
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
             if (!child->isVisible())
                continue;
            if(child->getIntegerAttribute("flex", 0) > 0) {
        //		child->setWidth((flex / flexes) * flexWidth);
            //	flex = (int)child->getAttribute("flex");
                child->setHeight((1 / flexes) * flexHeight);
            } else {
                statics++;
            }
        }

        // Now assign elements
        int top = 0;
        int bottom = 0;
        side = -1;
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if (!child->isVisible())
                continue;
            if(child->getIntegerAttribute("flex", 0) > 0) {

                side = 0;
            } else {
                if(side == 0)
                    side = 1;
            }
            if (side < 0)
            {
                child->setY(top);
            }
            else if (side == 0) {
                child->setY(topHeight + (((1 / flexes) * (flexHeight - 1)))*0 + child->getMargins()->top + this->getPadding()->top);

                child->setHeight(flexHeight);
            } else if(side > 0)
                child->setY(topHeight + flexHeight + bottom + child->getPadding()->top + child->getMargins()->top);


            child->setWidth(this->getWidth() - (child->getMargins()->bottom * 2 + this->getPadding()->bottom * 2));
            cout << "SPHBoxElement width: " << this->getHeight() << endl;
            cout << "VBoxElement Child: " << child->getType() << "Width: " << this->getWidth() << endl;

            switch(side) {
                case -1:
                    top += child->getHeight() ;
                    break;
                case 0:
                    top += child->getHeight();
                    break;
                case 2:
                    bottom += child->getHeight();
                    break;
                default:
                    top += child->getHeight();
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

