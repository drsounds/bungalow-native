#ifndef DOCTRINEVIEW_H
#define DOCTRINEVIEW_H
#include "../../space/include/SPContainerViewElement.h"
namespace space {
    class SPElement;
    class SPTextElement;
    namespace views {
        class DoctrineView : public SPContainerViewElement
        {
            public:
                DoctrineView(SPElement *parent);
                virtual ~DoctrineView();
                void navigate(string uri);
                bool acceptsUri(string uri);
            protected:
                SPTextElement *text;
            private:
        };
    }
}
#endif // DOCTRINEVIEW_H
