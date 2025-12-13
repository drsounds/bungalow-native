#include "StartView.h"
#include <regex>


namespace space {
    namespace views {
        StartView::StartView() {
        }
        StartView::StartView(SPElement *parent)
         : SPViewElement(parent)
        {
            this->clipView = false;
        	this->setUri("spacify:start");
        	this->setAttribute("src", "spacify:start");
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
