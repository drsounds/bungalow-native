#ifndef BOXELEMENT_H
#define BOXELEMENT_H
#include "SPElement.h"
#include "SPWindow.h"
#include <string>

using namespace std;

namespace spider {
class SPBoxElement : public SPElement {
public:
	explicit SPBoxElement(SPElement *parent);
  SPBoxElement(SPElement *parent, SPWindow *window);
	SPBoxElement();
	~SPBoxElement();
	void pack();
	virtual string gettype() {
		return "box";
	}

};
}
#endif // BOXELEMENT_H
