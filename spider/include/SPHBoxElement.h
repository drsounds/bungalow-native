#ifndef HBOXELEMENT_H
#define HBOXELEMENT_H
#include "SPElement.h"
namespace spider {
    class SPHBoxElement : public SPElement {

    public:
        SPHBoxElement(SPElement *parent) : SPElement(parent) {

        }
        virtual string getType() {
            return "hbox";
        }
        SPHBoxElement();
        void pack();
    };
}
#endif // HBOXELEMENT_H
