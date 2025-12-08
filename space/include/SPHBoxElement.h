#ifndef HBOXELEMENT_H
#define HBOXELEMENT_H
#include "SPElement.h"
namespace space {
    class SPElement;
    class SPHBoxElement : public SPElement {

    public:
        explicit SPHBoxElement(SPElement *parent): SPElement(parent) {}
        virtual string getType() {
            return "hbox";
        }
        SPHBoxElement() {}
        void pack();
    };
}
#endif // HBOXELEMENT_H
