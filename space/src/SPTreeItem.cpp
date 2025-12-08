#include "SPTreeItem.h"
#include "SPUri.h"
#include <regex>
namespace space {
    SPTreeItem::SPTreeItem(SPUri *uri) {
        this->highlighted = false;
        this->uri = uri;
        this->selected = false;
        this->setText("Loading...");
        if (std::regex_match(uri->uri, std::regex("spacify:internal:start"))) {
            this->setText("Start");
        }
    }
}
