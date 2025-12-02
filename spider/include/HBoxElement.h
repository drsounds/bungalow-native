#ifndef HBOXELEMENT_H
#define HBOXELEMENT_H
#include "Element.h"
namespace spider {
    class Element;
    #ifdef ELEMENT_CLASS
    #ifndef HBOX_ELEMENT
    class HBoxElement : public Element {

    public:
        HBoxElement(Element *parent) : Element(parent) {

        }
        virtual string getType() {
            return "hbox";
        }
        HBoxElement();
        void pack();
    };
    #define HBOX_ELEMENT
    #endif
    #endif
}
#endif // HBOXELEMENT_H
