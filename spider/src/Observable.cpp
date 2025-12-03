#include "Observable.h"
namespace spider {
Observable::Observable()
{
	//ctor
	this->observers = new list<Observer *>;
}

void Observable::dispatchEvent(const string& event, EventArgs* args, SPType* sender)
{
	this->notify(event, sender, args);
}

void Observable::notify(const string& evt, SPType *sender, EventArgs *data) const
{
	for(auto observer : *this->observers) {
		string t = observer->getEvent();
		if(t == (evt)) {
			sp_callback cb = observer->getCallback();
			cb(evt, sender, data);
		}
	}
}
void Observable::addEventListener(const string& type, const sp_callback& callback) {
	auto *observer = new Observer(type, callback);
	this->observers->push_back(observer);

}

Observable::~Observable()
{
	//dtor
}

}
