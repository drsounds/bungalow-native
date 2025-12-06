#include "SPElement.h"

#include <string>
using namespace std;


namespace spider {
    class SPDOMViewElement : public SPElement {
    private:
    public:
        int parseDepth;
        DOMViewElement () {

        }
        DOMViewElement(SPElement *parent);

        void loadXML(string buffer);
    };
    string getAttribute(const string &attribute, const string *attributes, const string &defValue);

    void startElement(void *data, const string &el, const string *attr);
    void endElement(void *data, const string &el);
}
