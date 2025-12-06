#ifndef TOPLISTVIEW_H
#define TOPLISTVIEW_H
#include "SPContainerViewElement.h"

namespace spider {
    class SPElement;
    namespace views {
        class TopListView : public SPContainerViewElement
        {
            public:
                TopListView();
                TopListView(SPElement *parent);
                virtual ~TopListView();
                bool acceptsUri(string uri);
                void navigate(string uri);
                string getType();
                virtual void scroll(int scrollX, int scrollY, int x, int y);
        };
    }
}

#endif // TOPLISTVIEW_H
