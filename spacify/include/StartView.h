#ifndef STARTVIEW_H
#define STARTVIEW_H
#include "SPViewElement.h"
#include <string>
using namespace std;
namespace space {
    namespace views {
        class StartView : public SPViewElement
        {
            public:
                StartView();
                explicit StartView(SPElement *parent);
                virtual ~StartView();
                bool acceptsUri(const string& uri) override;
                virtual string getType();
            protected:
            private:
        };
    }
}
#endif // STARTVIEW_H
