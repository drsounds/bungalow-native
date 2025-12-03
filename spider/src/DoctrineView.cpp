#include "DoctrineView.h"

#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "TextElement.h"
#include "Element.h"
#include "GraphicsContext.h"

using namespace std;

namespace spider {
    namespace views {
        DoctrineView::DoctrineView(Element *parent)
         : ContainerViewElement(parent)
        {
            this->getPadding()->top = 20;
            this->getPadding()->left = 20;
            //ctor
            text = new TextElement(this);
            text->setInnerText("Doctrine");
            text->set("height", "160");
            text->set("fgcolor", "#99CC00");
            text->set("size", "25");
            text->set("width", "100%");
            this->appendChild(text);
        }

        bool DoctrineView::acceptsUri(string uri) {
            string uri2 = uri.c_str();
            bool a = std::regex_match(uri2, regex("spacify:doctrine:(.*)"));
            return a;
        }

        void DoctrineView::navigate(string uri) {

            vector<string> strs;
            boost::split(strs, uri, boost::is_any_of(":")); 
            this->text->setInnerText(strs.at(2));
        }

        DoctrineView::~DoctrineView()
        {
            //dtor
        }
    }
}
