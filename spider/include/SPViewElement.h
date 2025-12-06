#ifndef VIEWELEMENT_H
#define VIEWELEMENT_H
#include "SPVBoxElement.h"
#include <string>
using namespace std;
namespace spider {
    class SPViewElement : public SPVBoxElement
    {
        public:
            string loadView(string view);
            void request(string uri);
            SPViewElement();
            SPViewElement(SPElement *parent);
            virtual ~SPViewElement();
            virtual void navigate(string uri);
            virtual bool acceptsUri(string uri) {
                return false;
            }
            virtual void scroll(int scrollX, int scrollY, int mouseX, int mouseY);
            void pack();
        protected:
        private:
    };
}
#endif // VIEWELEMENT_H
