#ifndef PLAYQUEUEVIEW_H
#define PLAYQUEUEVIEW_H
#include <regex>
#include "Element.h"
#include "ViewElement.h"
#include "ContainerViewElement.h"
namespace spider {
    namespace views {
        #ifdef CONTAINERVIEWELEMENT_CLASS
        #ifndef PLAYQUEUEVIEW_CLASS

        class PlayQueueView : public ContainerViewElement
        {
            public:
                PlayQueueView();
                PlayQueueView(Element *parent);
                void navigate(string uri);
                bool acceptsUri(string uri);
                virtual ~PlayQueueView();
                string getType();
            protected:
            private:
        };
        #define PLAYQUEUEVIEW_CLASS
        #endif
        #endif
    }
}


#endif // PLAYQUEUEVIEW_H