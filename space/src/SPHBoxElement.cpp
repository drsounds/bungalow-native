#include "SPHBoxElement.h"

#include <iostream>

#include "SPElement.h"


namespace space {
    void SPHBoxElement::pack() {
        SPElement::pack();
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
        if (flexWidth < 1)
        {
            flexWidth = 1;
        }
        for(std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPElement *child = (SPElement *)*it;
            int flex = child->getIntegerAttribute("flex", 0);
            if(flex > 0) {
            	child->setWidth((flex / flexes) * flexWidth - 1);
            } else {
                statics++;
            }
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
                child->setX(left);
            else if(side == 0) {
                child->setX(leftWidth);

            }
            else
            {
                child->setX(leftWidth + flexWidth + right);
            }
            child->setY(this->getPadding()->top);

            child->setHeight(this->getHeight());
            //cout << "SPHBoxElement height: " << this->getHeight() << endl;
            //cout << "SPHBoxElement Child: " << child->getType() << " Height: " << this->getHeight() << endl;
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
        cout << "Element: " << this->getType() << " packed to width: " << this->getWidth() << " height: " << this->getHeight() << " flex: " << this->getIntegerAttribute("flex", 0) << endl;
    };

}
