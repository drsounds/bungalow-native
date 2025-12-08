#ifndef CONTAINERVIEWELEMENT_H
#define CONTAINERVIEWELEMENT_H
#include "SPViewElement.h"

namespace space {
    class SPElement;
    class SPContainerViewElement : public SPViewElement
    {
        public:
            SPContainerViewElement(SPElement *parent);
            SPContainerViewElement();
            virtual ~SPContainerViewElement();
        protected:
        private:
    };
    
}

#endif // CONTAINERVIEWELEMENT_H
