#ifndef PLAYQUEUEVIEW_H
#define PLAYQUEUEVIEW_H

#include <string>

#include "SPContainerViewElement.h"

using namespace std;

namespace space {
    class SPElement;
    namespace views {
        class PlayQueueView : public SPContainerViewElement
        {
            public:
                PlayQueueView();
                PlayQueueView(SPElement *parent);
                void navigate(string uri);
                bool acceptsUri(string uri);
                virtual ~PlayQueueView();
                string getType();
            protected:
            private:
        };
    }
}


#endif // PLAYQUEUEVIEW_H