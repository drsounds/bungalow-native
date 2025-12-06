#include "PlayQueueView.h"
#include <regex>
#include "SPMockTableDataSource.h"
#include "SPTableElement.h"
using namespace std;
namespace spider {
    namespace views {
        PlayQueueView::PlayQueueView()
         : SPContainerViewElement()
        {
            //ctor
        }
        string PlayQueueView::getType() {

            return "playqueueview";

        }
        PlayQueueView::PlayQueueView(SPElement *parent)
            : SPContainerViewElement(parent)
        {
            this->clipView = true;
            //ctor
            /*HeatherElement *headerElement = new HeaderElement(this);
            headerElement->title->setTitle("Test");
            this->appendChild(headerElement);*/
            auto *tableView = new SPTableElement(this, new spider::SPMockTableDataSource());
            this->appendChild(tableView);
            tableView->setHeight(100);
        }
        void PlayQueueView::navigate(string uri) {

        }
        bool PlayQueueView::acceptsUri(string uri) {
            return std::regex_match(uri.c_str(), std::regex("spacify:internal:(history|playqueue)"));
        }
        PlayQueueView::~PlayQueueView()
        {
            //dtor
        }
    }
}
