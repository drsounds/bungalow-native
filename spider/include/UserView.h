#ifndef USERVIEW_H
#define USERVIEW_H
#include "TabbarViewElement.h"

#include "HeaderElement.h"
#include <string>
using namespace std;
namespace spider {
    namespace views {
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
