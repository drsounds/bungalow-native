#ifndef VBOXELEMENT_H
#define VBOXELEMENT_H
#include "BoxElement.h"
#include <string>
using namespace std;
namespace spider {
    class BoxElement;
    #ifdef BOXELEMENT_CLASS	
    #ifndef VBOXELEMENT_CLASS
    class VBoxElement : public BoxElement {

	public:
	    VBoxElement(Element *parent) : BoxElement(parent) {
		}
		VBoxElement();
        virtual string getType() {
            return "vbox";
        }
		void pack();
	};
    #define VBOXELEMENT_CLASS
    #endif
	#endif
}
#endif // VBOXELEMENT_H
