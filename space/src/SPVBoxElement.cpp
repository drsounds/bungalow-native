#include "SPVBoxElement.h"

#include <iostream>

namespace space {
	SPVBoxElement::SPVBoxElement(SPElement *parent) : SPElement(parent) {
		this->setTagName("vbox");
	}

    void SPVBoxElement::pack() {
        SPElement::pack();
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
            if(child->getFlex() > 0) {
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
        if (flexHeight < 1)
        {
            flexHeight = 1;
        }
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
             if (!child->isVisible())
             	continue;
        	int topPadding = this->getPadding().top + child->getMargins().top;
        	int bottomPadding = this->getPadding().bottom - child->getMargins().bottom;
            int flex = child->getFlex();
            if(flex > 0) {
            	child->setHeight((1 / flexes) * flexHeight - bottomPadding - topPadding);
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
        	int leftPadding = this->getPadding().left + child->getMargins().left;
        	int rightPadding = this->getPadding().right + child->getMargins().right;
        	int topPadding = this->getPadding().top + child->getMargins().top;
        	int bottomPadding = this->getPadding().bottom - child->getMargins().bottom;
            if(child->getFlex() > 0) {
                side = 0;
            } else {
                if(side == 0)
                    side = 1;
            }
            if (side < 0)
            {
                child->setY(top + topPadding);
            }
            else if (side == 0) {
                child->setY(topHeight + topPadding);

                child->setHeight(flexHeight - bottomPadding);
            }
            else
            {
                child->setY(topHeight + flexHeight + bottom + topPadding);
            }
        	child->setX(leftPadding);
            child->setWidth(this->getWidth() - rightPadding - leftPadding);

            switch(side) {
                case -1:
                    top += child->getHeight();
                    break;
                case 0:
                    top += child->getHeight();
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
        //cout << "VBoxElement#" << this->getId() << " packed to width: " << this->getWidth() << " height: " << this->getHeight() << endl;

    };
}