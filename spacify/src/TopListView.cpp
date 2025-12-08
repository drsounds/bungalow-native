#include "TopListView.h"
#include "SPHBoxElement.h"
#include "SPTableElement.h"
#include "SPMockTableDataSource.h"
#include "SPVBoxElement.h"
#include <regex>
namespace space {
    namespace views {
        TopListView::TopListView() :
            SPContainerViewElement::SPContainerViewElement() {
        }
        string TopListView::getType() {
            return "toplistview";
        }
        TopListView::TopListView(SPElement *parent)
            : SPContainerViewElement::SPContainerViewElement(parent)
        {

            this->clipView = true;
             // Build the view
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
            title->set("flex", "1");
            title->set("size", "16");
            hbox->appendChild(title);
            SPTableElement *tableView = new SPTableElement(this, new SPMockTableDataSource());
            this->appendChild(tableView);
        }
        void TopListView::scroll(int scrollX, int scrollY, int x, int y) {
            SPElement::scroll(scrollX, scrollY, x, y);
        }
        void TopListView::navigate(string uri) {

        }
        bool TopListView::acceptsUri(string uri) {
            return std::regex_match(uri.c_str(), std::regex("spacify:internal:toplist"));
        }
        TopListView::~TopListView()
        {
            //dtor
        }
    }
}
