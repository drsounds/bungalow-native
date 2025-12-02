#include "PlayQueueView.h"
#include "HeaderElement.h"
#include "TableElement.h"
#include "MockTableDataSource.h"
using namespace std;
namespace spider {
    namespace views {
        PlayQueueView::PlayQueueView()
         : ContainerViewElement()
        {
            //ctor
        }
        string PlayQueueView::getType() {

            return "playqueueview";

        }
        PlayQueueView::PlayQueueView(Element *parent)
            : ContainerViewElement(parent)
        {
            this->clipView = true;
            //ctor
            /*HeatherElement *headerElement = new HeaderElement(this);
            headerElement->title->setTitle("Test");
            this->appendChild(headerElement);*/
            TableElement *tableView = new TableElement(this, new MockTableDataSource());
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
