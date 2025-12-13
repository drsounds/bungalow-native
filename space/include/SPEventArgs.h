#ifndef EVENTARGS_H
#define EVENTARGS_H
#include "SPObject.h"
namespace space {
class SPObject;
class SPEventArgs : public SPObject
{
protected:
	SPObject *sender;
public:
    SPEventArgs();
    ~SPEventArgs() override;
	SPObject *getSender() const {
		return sender;
	}
	void setSender(SPObject *value) {
		this->sender = value;
	}
};
class SPAttributeChangedEventArgs : public SPEventArgs {
private:
	string attributeName;
	string newValue;
	string oldValue;
	string attributeType;
public:
	SPAttributeChangedEventArgs(const string &attributeName,
	                            const string &newValue, const string &oldValue, const string &attributeType);

	void setAttributeName(const string& value) {
		this->attributeName = value;
	}
	void setNewValue(const string& value) {
		this->newValue = value;
	}
	void setOldValue(const string& value) {
		this->oldValue = value;
	}
	string getAttributeType() {
		return attributeType;
	}
	void setAttributeType(const string& value) {
		this->attributeType = value;
	}
	string getAttributeName() {
		return attributeName;
	}
	string getNewValue() {
		return newValue;
	}
	string getOldValue() {
		return oldValue;
	}
};
}

#endif // EVENTARGS_H
