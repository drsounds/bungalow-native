#ifndef BOXELEMENT_H
#define BOXELEMENT_H
#include "Element.h"
#include <string>

using namespace std;

namespace spider {
class BoxElement;
class Element;
#ifdef ELEMENT_CLASS
#ifndef BOXELEMENT_CLASS
class BoxElement : public Element {

public:
	BoxElement(Element *parent);
	BoxElement();
	~BoxElement();
	void pack();
	virtual string gettype() {
		return "box";
	}

};
#define BOXELEMENT_CLASS
#endif
#endif
}
#endif // BOXELEMENT_H
