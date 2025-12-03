#ifndef WHATSNEWVIEW_H
#define WHATSNEWVIEW_H
#include "ContainerViewElement.h"

namespace spider {
    class Element;
    namespace views {
        class WhatsNewView : public ContainerViewElement
        {
            public:
                WhatsNewView();
                WhatsNewView(Element *parent);
                virtual ~WhatsNewView();
                void navigate(string uri);
                bool acceptsUri(string uri);
                string getType();
        };
    }
}

#endif // WHATSNEWVIEW_H
