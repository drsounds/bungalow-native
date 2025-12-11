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

        SPViewElement *view = (SPViewElement *)child;
        string type = view->getType();
        if (boost::algorithm::ends_with(type, "view")) {

            SPNode::appendChild(child);
            cout << "valid view: " << type << endl;

            ((SPElement *)child)->setVisible(false);
            view->set("flex", "1");
        } else {
            exit(0);
        }
    }
    SPViewStackElement::SPViewStackElement() {
         this->history = new std::stack<string>;
         this->future = new std::stack<string>;
    }

    SPViewStackElement::SPViewStackElement(SPElement *parent)
     : SPVBoxElement::SPVBoxElement(parent) {
         this->setParent(this);
         this->history = new std::stack<string>;
         this->future = new std::stack<string>;
         this->activeView = nullptr;
        vector<SPNode *> *children = this->getChildNodes();
    }
    void SPViewStackElement::pack() {
        SPVBoxElement::pack();
         for (std::vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            SPNode *node = static_cast<SPNode *>(*it);
            SPElement *view = (SPElement *)node;
            string type = view->getType();
            view->setIntegerAttribute("flex", 1);
            view->setWidth(this->getWidth() - (view->getMargins()->bottom * 2 + this->getPadding()->bottom * 2));
            // cout << "View of type: " << type << endl;
            if (view->absoluteBounds != NULL && this->absoluteBounds != NULL) {
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
        for (auto & it : *this->getChildNodes()) {
            auto *node = static_cast<SPNode *>(it);
            auto view = static_cast<SPViewElement*>(node);
            string type = view->getType();
            std::cout << view->getType() << std::endl;
            if (ends_with(type, "view")) {
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

            } else {
                cout << "Wrong view: " << view->getType() << endl;
            }
            this->invalidate();

            if (std::regex_match(uri.c_str(), std::regex("spacify:internal:start"))) {

                // Show What's new view
                view = new views::WhatsNewView((SPElement *)this);

            } /* else if (std::regex_match(uri.c_str(), std::regex("^spacify:internal:playqueue"))) {

                // Show playqueue view and switch to the queue tab

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:internal:history"))) {

                // Show playqueue view and switch to the history tab

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:config"))) {

                // Show spacify config page

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:artist:(.*)"))) {

                // Load artist view and navigate to apporiate artist

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:album:(.*)"))) {

                // Load album view and navigate to apporiate artist

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:user:(.*):playvector:(.*)"))) {

                // Load user playvectors view

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:internal:radio"))) {

                // Load radio view

            } else if (std::regex_match(uri.c_str(), std::regex("^spacify:config2"))) {

                // Show the extended config2 dialog

            } else {

                // Show error message (The URI could not be found)
                return;
            }*/
            vector<SPNode *> *children = this->getChildNodes();
            if (view != nullptr) {
                this->appendChild(view);
                view->navigate(uri);
            }
        }



    }



}
