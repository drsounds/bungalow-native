#ifndef USERVIEW_H
#define USERVIEW_H
#include "SPViewElement.h"
#include <string>
using namespace std;
namespace spider {
    class SPHeaderElement;
    class SPElement;
    namespace views {
        class UserView : public SPViewElement
        {
            public:
                UserView();
                UserView(SPElement *parent);
                virtual ~UserView();
                bool acceptsUri(string uri);
                void navigate(string uri);
            protected:
                SPHeaderElement *header;
            private:
        };
    }
}
#endif // USERVIEW_H
