#ifndef STARTVIEW_H
#define STARTVIEW_H
#include "SPTabbarViewElement.h"
#include <string>
using namespace std;
namespace space {
    namespace views {
        class StartView : public SPTabbarViewElement
        {
            public:
                StartView();
                StartView(SPElement *parent);
                virtual ~StartView();
                bool acceptsUri(const string& uri) override;
                virtual string getType();
            protected:
            private:
        };
    }
}
#endif // STARTVIEW_H
