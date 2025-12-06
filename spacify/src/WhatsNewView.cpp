#include "WhatsNewView.h"
#include "SPButtonElement.h"
#include "SPHBoxElement.h"
#include "SPTableElement.h"
#include "SPColor.h"

#include <regex>

namespace spider {
    namespace views {
        WhatsNewView::WhatsNewView()
         : SPContainerViewElement::SPContainerViewElement()
        {
            this->clipView = true;
            //ctor
        }

        bool WhatsNewView::acceptsUri(string uri) {
            return std::regex_match(uri.c_str(), std::regex("spacify:internal:start"));
        }
        WhatsNewView::WhatsNewView(SPElement *parent)
         : SPContainerViewElement::SPContainerViewElement(parent)
        {


            // Build the view
            SPHBoxElement *hbox = new SPHBoxElement(this);
            hbox->getPadding()->top = 12;
            hbox->getPadding()->left = 16;
            hbox->getPadding()->bottom = 12;
            hbox->getPadding()->right =  16;



            hbox->set("height", "60");

            this->appendChild(hbox);

            // Add Header
            SPHBoxElement *title = new SPHBoxElement(hbox);
            title->set("fgcolor", "#aaffaa");
            title->setInnerText("What's New\0");
            title->set("height", "60");
            title->set("width", "120");
            title->set("size", "16");
            hbox->appendChild(title);

            // Add flex
            SPHBoxElement *hspacer = new SPHBoxElement(hbox);
            hspacer->set("flex", "1");
            hspacer->set("width", "100%");
            hspacer->set("heigh", "60");
            hbox->appendChild(hspacer);

            // Add more button
            SPButtonElement *more = new SPButtonElement(hbox);
            more->set("width", "150");
            more->set("height", "60");
            more->set("fgcolor", "#000000");
            more->set("bgcolor", "#878787");
            more->setInnerText("More\0");
            more->set("size", "11");
            hbox->appendChild(more);


            SPHBoxElement *whatsNew1 = new SPHBoxElement(this);
            whatsNew1->set("height", "500");
            this->appendChild(whatsNew1);

            // Create next chapter
            SPHBoxElement *hbox2 = new SPHBoxElement(this);
            hbox2->getPadding()->top = 12;
            hbox2->getPadding()->left = 16;
            hbox2->getPadding()->bottom = 12;
            hbox2->getPadding()->right =  16;
            hbox2->set("height", "200");
            this->appendChild(hbox2);

            SPHBoxElement *title2 = new SPHBoxElement(hbox);
            title2->setColorAttribute("fgcolor", SPColor(255, 127, 255, 1));
            title2->setInnerText("Artists you might like \0");
            title2->setIntegerAttribute("height", 60);
            title2->setIntegerAttribute("width", 620);
            title2->setIntegerAttribute("size", 16);
            hbox2->appendChild(title2);

        }
        string WhatsNewView::getType() {
            return "whatsnewview";
        }
        void WhatsNewView::navigate(string uri) {

        }
        WhatsNewView::~WhatsNewView()
        {
            //dtor
        }
    }
}
