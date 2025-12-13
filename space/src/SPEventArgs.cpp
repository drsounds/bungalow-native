#include "SPEventArgs.h"

namespace space {
SPEventArgs::SPEventArgs()
{
    //ctor
}

SPEventArgs::~SPEventArgs()
{
    //dtor
}

SPAttributeChangedEventArgs::SPAttributeChangedEventArgs(const string& attributeName,
	const string& newValue, const string& oldValue, const string& attributeType) {
	this->attributeName = attributeName;
	this->newValue = newValue;
	this->oldValue = oldValue;
	this->attributeType = attributeType;
}
}
