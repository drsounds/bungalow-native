#include "SPViewStackElement.h"

#include <iostream>

#include "WhatsNewView.h"
#include <regex>
#include "SPWindowElement.h"
#include "PlayQueueView.h"
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
namespace space {
    void SPViewStackElement::appendChild(SPNode *child) {
    	SPNode::appendChild(child);
        SPViewElement *view = (SPViewElement *)child;
        string type = view->getType();
        cout << "valid view: " << type << endl;
        ((SPElement *)child)->setVisible(false);
        view->setIntegerAttribute("flex", 1);
    	this->pack();
    }
    SPViewStackElement::SPViewStackElement() {
         this->history = new std::stack<string>;
         this->future = new std::stack<string>;
    }

    SPViewStackElement::SPViewStackElement(SPElement *parent)
     : SPVBoxElement::SPVBoxElement(parent) {
    	this->setTagName("viewstack");
        this->history = new std::stack<string>;
        this->future = new std::stack<string>;
        this->activeView = nullptr;
    }
    void SPViewStackElement::pack() {
        SPVBoxElement::pack();
         for (vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPNode *node = static_cast<SPNode *>(*it);
            SPElement *view = (SPElement *)node;
            string type = view->getType();
            view->setIntegerAttribute("flex", 1);
            view->setWidth(this->getWidth() - (view->getMargins()->bottom * 2 + this->getPadding()->bottom * 2));
            // cout << "View of type: " << type << endl;
            if (view->absoluteBounds != nullptr && this->absoluteBounds != nullptr) {
                view->absoluteBounds->height = this->absoluteBounds->height;
                view->absoluteBounds->width = this->absoluteBounds->width;
            }
         }
    }
    /**
     * Main navigation handler inside spacify
     **/
    void SPViewStackElement::navigate(const string& uri) {
        // TODO add navigation handler
        // Hide all views
        this->pack();
        this->invalidate();
        SPViewElement *newView = NULL;
        bool foundView = false;
    	for (std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
    		SPNode *node = static_cast<SPNode *>(*it);
    		SPViewElement *view = (SPViewElement *)node;
    		string type = view->getType();
    		std::cout << view->getType() << std::endl;
    		if (view->acceptsUri(uri)) {
    			std::cout << uri << std::endl;
    			std::cout << view->getType() << std::endl;
    			cout << "View " << view->getType() << " shown" << endl;
    			view->setVisible(true);
    			view->navigate(uri);
    			activeView = view;
    		} else {
    			cout << "View " << view->getType() << " hidden" << endl;
    			view->setVisible(false);
    		}
    		this->invalidate();
    		this->pack();
    	}
    }
}
