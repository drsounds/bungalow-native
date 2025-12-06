#include "SPTreeItem.h"
#include <regex>
namespace spider {
    SPTreeItem::SPTreeItem(SPUri *uri) {
        this->highlighted = false;
        this->uri = uri;
        this->setText("Loading...");
        if (std::regex_match(uri->uri, std::regex("spacify:internal:start"))) {
            this->setText("Start");
        }
    }
}
