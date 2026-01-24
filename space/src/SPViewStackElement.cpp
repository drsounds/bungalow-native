#include "SPViewStackElement.h"

#include <iostream>
#include <regex>
#include <vector>

#include "SPGraphicsContext.h"
#include "WxWidgetsGraphicsContext.h"
#include <wx/wx.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "WhatsNewView.h"
#include "SPWindowElement.h"
#include "PlayQueueView.h"
#include "SPUri.h"
#include "Timer.h"


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
        // cout << "valid view: " << type << endl;
        ((SPElement *)child)->setVisible(false);
        view->setFlex( 1);
    	this->pack();
    }
    SPViewStackElement::SPViewStackElement() {
         this->history = new std::stack<string>;
         this->future = new std::stack<string>;
    }

    SPViewStackElement::SPViewStackElement(SPElement *parent)
     : SPVBoxElement(parent) {
    	this->setTagName("viewstack");
        this->history = new std::stack<string>;
        this->future = new std::stack<string>;
        this->activeView = nullptr;
    }
    void SPViewStackElement::pack() {
        SPVBoxElement::pack();
    }
    /**
     * Main navigation handler inside spacify
     **/
    void SPViewStackElement::navigate(const string& value) {
        // TODO add navigation handler
        // Hide all views
        this->pack();
        this->invalidate();
        SPViewElement *newView = NULL;
        bool foundView = false;
    	SPUri uri(value);
    	for (std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
    		SPNode *node = static_cast<SPNode *>(*it);
    		SPViewElement *view = (SPViewElement *)node;
    		string type = view->getType();
    		// std::cout << view->getType() << std::endl;
    		if (view->acceptsUri(uri.getAddress())) {
                this->freeze();
    			//std::cout << uri << std::endl;
    			//std::cout << view->getType() << std::endl;
    			//cout << "View " << view->getType() << " shown" << endl;
    			view->setVisible(true);
    			view->navigate(uri.getAddress());
    			view->setHash(uri.getHash());
    			activeView = view;
                this->scheduleThaw(100);
    		} else {
    			// cout << "View " << view->getType() << " hidden" << endl;
    			view->setVisible(false);
    		}
    		this->invalidate();
    		this->pack();
    	}
    }
}
