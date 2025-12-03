#ifndef HEADERELEMENT_H
#define HEADERELEMENT_H
#include "HBoxElement.h"
namespace spider {
    class ImageElement;
    class Element;
    class TitleElement;
    class HeaderElement : public HBoxElement
    {
        public:
            HeaderElement();
            HeaderElement(Element *parent);
            virtual ~HeaderElement();
            TitleElement *title;
            ImageElement *image;
            virtual string getType();
        protected:
        private:
    };
}

#endif // HEADERELEMENT_H
