#ifndef VIEWELEMENT_H
#define VIEWELEMENT_H
#include "SPVBoxElement.h"
#include <string>
using namespace std;
namespace space {
    class SPViewElement : public SPVBoxElement
    {
        public:
            SPViewElement();
            SPViewElement(SPElement *parent);
            virtual ~SPViewElement();
            virtual void navigate(const string& uri);
            virtual bool acceptsUri(const string& uri);
            virtual void scroll(int scrollX, int scrollY, int mouseX, int mouseY);
            void pack();
    };
}
#endif // VIEWELEMENT_H
