#ifndef DOCTRINEVIEW_H
#define DOCTRINEVIEW_H
#include "ContainerViewElement.h"
namespace spider {
    namespace views {
        class TextElement;
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
    }
}
#endif // DOCTRINEVIEW_H
