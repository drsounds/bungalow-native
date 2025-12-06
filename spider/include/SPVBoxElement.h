#ifndef VBOXELEMENT_H
#define VBOXELEMENT_H
#include "SPBoxElement.h"

#include "SPWindow.h"

#include <string>
using namespace std;
namespace spider {
	class SPElement;
	class SPWindow;
	class SPVBoxElement : public SPBoxElement {

	public:
		SPVBoxElement(SPElement *parent) : SPBoxElement(parent) {}
		SPVBoxElement(SPElement *parent, SPWindow *window) : SPBoxElement(parent, window) {}
		SPVBoxElement();
		explicit SPVBoxElement(SPWindowElement* parent);

		virtual string getType() {
			return "vbox";
		}
		void pack();
	};
}
#endif // VBOXELEMENT_H
