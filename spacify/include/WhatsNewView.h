#ifndef WHATSNEWVIEW_H
#define WHATSNEWVIEW_H
#include "SPContainerViewElement.h"

namespace space {
    class SPElement;
    namespace views {
        class WhatsNewView : public SPContainerViewElement
        {
            public:
                WhatsNewView();
                WhatsNewView(SPElement *parent);
                virtual ~WhatsNewView();
                void navigate(string uri);
                bool acceptsUri(string uri);
                string getType();
        };
    }
}

#endif // WHATSNEWVIEW_H
