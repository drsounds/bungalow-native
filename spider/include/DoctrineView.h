#ifndef DOCTRINEVIEW_H
#define DOCTRINEVIEW_H
#include "ContainerViewElement.h"
#include "TextElement.h"
namespace spider {
    namespace views {
        class DoctrineView;
        #ifdef CONTAINERVIEWELEMENT_CLASS
        #ifdef TEXTELEMENT_CLASS
        #ifndef DOCTRINEVIEW_CLASS
        class DoctrineView : public ContainerViewElement
        {
            public:
                DoctrineView(Element *parent);
                virtual ~DoctrineView();
                void navigate(string uri);
                bool acceptsUri(string uri);
            protected:
                TextElement *text;
            private:
        };
        #define DOCTRINEVIEW_CLASS
        #endif
        #endif
        #endif
    }
}
#endif // DOCTRINEVIEW_H
