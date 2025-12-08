#ifndef VBOXELEMENT_H
#define VBOXELEMENT_H
#include "SPElement.h"

#include "SPWindow.h"

#include <string>
using namespace std;
namespace spider {
	class SPElement;
	class SPWindow;
	class SPVBoxElement : public SPElement {

	public:
		explicit SPVBoxElement(SPElement *parent) : SPElement(parent) {}
		SPVBoxElement(SPElement *parent, SPWindow *window) : SPElement(parent, window) {}
		SPVBoxElement() {}

		virtual string getType() {
			return "vbox";
		}
		void pack();
	};
}
#endif // VBOXELEMENT_H
