#include "SPHBoxElement.h"

#include <iostream>

#include "SPElement.h"


namespace space {
	SPHBoxElement::SPHBoxElement(SPElement *parent) {
		this->setTagName("hbox");
	}
    void SPHBoxElement::pack() {
        SPElement::pack();
        int flexes = 0;
        int statics = 0;
        int leftWidth = 0;
        int rightWidth = 0;
        // First calculate count of flex
		int thisFlex = this->getFlex();
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
        	SPElement *child = (SPElement *)*it;
        	if (!child->isVisible())
        		continue;
            if(child->getFlex() > 0) {
                flexes++;
            } else {
                statics++;
                leftWidth += child->getWidth();
            }
        }

        int flexWidth = flexes > 0 ? (this->getWidth() - leftWidth - rightWidth) / flexes : 0;

        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            int flex = child->getFlex();
            if(flex > 0) {
            	child->setWidth((flex / flexes) * flexWidth - 1 - (child->getMargins()->right * 2 + this->getPadding()->right * 2));
            } else {
                statics++;
            }
        }

        // Now assign elements
        int left = 0;
        int right = 0;

		int side = -1;
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
	        SPElement *child = (SPElement *)*it;
        	if (!child->isVisible())
        		continue;
        	if(child->getFlex() > 0) {
        		side = 0;
        	} else {
        		if(side == 0)
        			side = 1;
        	}
        	if(side < 0)
        	{
        		child->setX(left + child->getMargins()->top + this->getPadding()->top);
        	}
			else if(side == 0)
			{
                child->setX(leftWidth + child->getMargins()->left + this->getPadding()->left);
				child->setWidth(flexWidth);
            }
            else
            {
                child->setX(leftWidth + flexWidth + right + this->getPadding()->left + child->getMargins()->left);
            }
            child->setY(this->getPadding()->top);
			int height = this->getHeight();
            child->setHeight(height - (child->getMargins()->top * 2 + this->getPadding()->top * 2));
            switch(side) {
            case -1:
                left += child->getWidth();
                break;
            case 0:
            	left += child->getWidth();
                break;
            case 1:
                right += child->getWidth();
            	break;
            default:
            	right += child->getWidth();
            }
        }
        // Pack child elements
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            if (!child->isVisible())
                continue;
            child->pack();
        }
        // cout << "Element: " << this->getType() << " packed to width: " << this->getWidth() << " height: " << this->getHeight() << " flex: " << this->getFlex() << endl;
    };

}
