#include "LibraryView.h"

#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "SPTextElement.h"
#include "SPTableElement.h"
#include "SPElement.h"
#include "SPGraphicsContext.h"

using namespace std;

namespace space {
    namespace views {
        LibraryView::LibraryView(SPElement *parent)
            : SPTabBarViewElement(parent)
        {
            table = new SPTableElement(this);
            this->appendChild(table);
            table->setFlex(1);
        }

        bool LibraryView::acceptsUri(const string& uri) {
            string uri2 = uri.c_str();
            bool a = std::regex_match(uri2, regex("spacify:library"));
            return a;
        }

        void LibraryView::navigate(const string& uri) {
            this->setUri(uri);
        }

        LibraryView::~LibraryView()
        {
            //dtor
        }
    }
}
