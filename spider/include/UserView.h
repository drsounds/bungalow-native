#ifndef USERVIEW_H
#define USERVIEW_H
#include "ViewElement.h"
#include <string>
using namespace std;
namespace spider {
    namespace views {
        class HeaderElement;
        class Element;
        class UserView : public ViewElement
        {
            public:
                UserView();
                UserView(Element *parent);
                virtual ~UserView();
                bool acceptsUri(string uri);
                void navigate(string uri);
            protected:
                HeaderElement *header;
            private:
        };
    }
}
#endif // USERVIEW_H
