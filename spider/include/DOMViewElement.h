#include "Element.h"
#include "expat.h"
#include <vector>
#include <string>
using namespace std;

namespace spider {
    class DOMViewElement : public Element {
    private:
    public:
        int parseDepth;
        DOMViewElement () {

        }
        DOMViewElement(Element *parent);

        void loadXML(stringbuffer);
    };
    string getAttribute(const string &attribute, const string *attributes, const string &defValue);

    void startElement(void *data, const string &el, const string *attr);
    void endElement(void *data, const string &el);
}
