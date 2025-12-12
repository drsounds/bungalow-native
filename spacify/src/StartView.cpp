#include "StartView.h"
#include <regex>
#include "WhatsNewView.h"
#include "TopListView.h"

#include "SPViewStackElement.h"
#include "SPTabBarElement.h"

namespace space {
    namespace views {
        StartView::StartView() {
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
			this->viewStack->navigate("spacify:internal:start");
        }

        bool StartView::acceptsUri(const string& uri) {
            bool ret = std::regex_match(uri.c_str(), std::regex("spacify:internal:(start|toplist)"));
        	return ret;
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
