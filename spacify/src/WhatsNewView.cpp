#include "WhatsNewView.h"

#include "SPButtonElement.h"
#include "SPHBoxElement.h"
#include "SPTableElement.h"

#include <regex>

namespace space {
    namespace views {
        WhatsNewView::WhatsNewView()
         : SPContainerViewElement::SPContainerViewElement()
        {
            this->clipView = true;
            //ctor
        }

        bool WhatsNewView::acceptsUri(const string& uri) {
            bool ret = std::regex_match(uri.c_str(), std::regex("spacify:internal:start"));
        	return ret;
        }
        WhatsNewView::WhatsNewView(SPElement *parent)
         : SPContainerViewElement::SPContainerViewElement(parent)
        {
            // Build the view
            auto *hbox = new SPHBoxElement(this);
            hbox->getPadding()->top = 12;
            hbox->getPadding()->left = 16;
            hbox->getPadding()->bottom = 12;
            hbox->getPadding()->right =  16;

            hbox->set("height", "60");

            this->appendChild(hbox);

            // Add Header
            auto title = new SPHBoxElement(hbox);
            title->set("fgcolor", "#aaffaa");
            title->setInnerText("What's New");
            title->setHeight(60);
            title->setWidth(120);
            title->setIntegerAttribute("size", 16);
            hbox->appendChild(title);

            // Add flex
            auto hspacer = new SPHBoxElement(hbox);
            hspacer->setIntegerAttribute("flex", 1);
            hspacer->setHeight(60);
            hbox->appendChild(hspacer);

            // Add more button
            auto more = new SPButtonElement(hbox);
            more->setWidth(150);
            more->setHeight(60);
            more->setInnerText("More");
            more->setIntegerAttribute("size", 11);
            hbox->appendChild(more);

            auto whatsNew1 = new SPHBoxElement(this);
            whatsNew1->setHeight(500);
            this->appendChild(whatsNew1);

            // Create next chapter
            SPHBoxElement *hbox2 = new SPHBoxElement(this);
            hbox2->getPadding()->top = 12;
            hbox2->getPadding()->left = 16;
            hbox2->getPadding()->bottom = 12;
            hbox2->getPadding()->right =  16;
            hbox2->setHeight(200);
            this->appendChild(hbox2);

            SPHBoxElement *title2 = new SPHBoxElement(hbox);
            title2->setInnerText("Artists you might like");
            title2->setHeight(60);
            title2->setWidth(620);
            title2->setIntegerAttribute("size", 16);
            hbox2->appendChild(title2);

        }
        void WhatsNewView::navigate(const string& uri) {

        }
        WhatsNewView::~WhatsNewView()
        {
            //dtor
        }
    }
}
