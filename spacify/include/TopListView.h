#ifndef TOPLISTVIEW_H
#define TOPLISTVIEW_H
#include "ContainerViewElement.h"

namespace spider {
    class Element;
    namespace views {
        class TopListView : public ContainerViewElement
        {
            public:
                TopListView();
                TopListView(Element *parent);
                virtual ~TopListView();
                bool acceptsUri(string uri);
                void navigate(string uri);
                string getType();
                virtual void scroll(int scrollX, int scrollY, int x, int y);
        };
    }
}

#endif // TOPLISTVIEW_H
