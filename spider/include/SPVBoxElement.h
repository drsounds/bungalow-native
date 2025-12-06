#ifndef VBOXELEMENT_H
#define VBOXELEMENT_H
#include "SPBoxElement.h"
#include <string>
using namespace std;
namespace spider {
	class SPElement;
	class SPWindowElement;
    class SPVBoxElement : public SPBoxElement {

	public:
	    SPVBoxElement(SPElement *parent) : SPBoxElement(parent) {
		}
		SPVBoxElement();
	    explicit SPVBoxElement(SPWindowElement* parent);

	    virtual string getType() {
            return "vbox";
        }
		void pack();
	};
}
#endif // VBOXELEMENT_H
