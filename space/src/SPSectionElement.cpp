//
// Created by Alexander Forselius on 2025-12-18.
//

#include "SPSectionElement.h"

namespace space {
SPSectionElement::SPSectionElement(SPElement *parent) : SPVBoxElement(parent) {
	this->setTagName("section");
	this->setHeight(300);
}
void SPSectionElement::pack() {
	SPVBoxElement::pack();
}
}