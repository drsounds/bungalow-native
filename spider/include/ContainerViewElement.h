#ifndef CONTAINERVIEWELEMENT_H
#define CONTAINERVIEWELEMENT_H
#include "ViewElement.h"
#include "Element.h"

namespace spider {
    class ViewElement;
    class Element;
    #ifdef VIEWELEMENT_CLASS
    #ifndef CONTAINERVIEWELEMENT_CLASS
    class ContainerViewElement : public ViewElement
    {
        public:
            ContainerViewElement(Element *parent);
            ContainerViewElement();
            virtual ~ContainerViewElement();
        protected:
        private:
    };
    #define CONTAINERVIEWELEMENT_CLASS
    #endif
    #endif
    
}

#endif // CONTAINERVIEWELEMENT_H
