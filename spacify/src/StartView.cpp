#include "StartView.h"
#include <regex>
#include "WhatsNewView.h"
#include "TopListView.h"

#include "SPViewStackElement.h"
#include "SPTabBarElement.h"

namespace space {
    namespace views {
        StartView::StartView() : SPTabbarViewElement() {
        }
        StartView::StartView(SPElement *parent)
         : SPTabbarViewElement(parent)
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
