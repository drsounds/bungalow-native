#include "StartView.h"
#include <regex>
#include "WhatsNewView.h"
#include "TopListView.h"

#include "ViewStackElement.h"
#include "TabBarElement.h"

namespace spider {
    namespace views {
        StartView::StartView() : TabbarViewElement() {
        }
        StartView::StartView(Element *parent)
         : TabbarViewElement(parent)
        {
            this->clipView = false;
            //ctor
            this->viewStack->appendChild(new views::WhatsNewView(this->viewStack));
            this->viewStack->appendChild(new views::TopListView(this->viewStack));
            this->tabBar->addTab("Overview", "overview", "spacify:internal:start");
            this->tabBar->addTab("Top List", "toplist", "spacify:internal:toplist");
        }

        bool StartView::acceptsUri(string uri) {
            return std::regex_match(uri.c_str(), std::regex("spacify:internal:(start|toplist)"));
        }

        string StartView::getType() {
            return "startview";
        }

        StartView::~StartView()
        {
            //dtor
        }
    }
}
