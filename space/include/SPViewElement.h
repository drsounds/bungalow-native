#ifndef VIEWELEMENT_H
#define VIEWELEMENT_H
#include "SPVBoxElement.h"
#include <string>
using namespace std;
namespace space {
    class SPViewElement : public SPVBoxElement
    {
        public:
            string loadView(string view);
            void request(string uri);
            SPViewElement();
            SPViewElement(SPElement *parent);
            virtual ~SPViewElement();
            virtual void navigate(const string& uri);
            virtual bool acceptsUri(const string& uri) {
                return false;
            }
            virtual void scroll(int scrollX, int scrollY, int mouseX, int mouseY);
            void pack();
    };
}
#endif // VIEWELEMENT_H
