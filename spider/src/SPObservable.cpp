#include "SPObservable.h"

#include "libspider.h"
#include "SPObject.h"
#include "SPObserver.h"
#include "SPEventArgs.h"
#include "SPNode.h"

namespace spider {
	class SPNode;

	SPObservable::SPObservable()
{
	//ctor
	this->observers = new list<SPObserver *>;
}

void SPObservable::dispatchEvent(const string& event, SPEventArgs* args, SPObject* sender)
{
	this->notify(event, sender, args);
}

void SPObservable::notify(const string& evt, SPObject *sender, SPEventArgs *data) const
{
	for(auto observer : *this->observers) {
		string t = observer->getEvent();
		if(t == (evt)) {
			Callback cb = observer->getCallback();
			cb(evt, sender, data);
		}
	}
}
void SPObservable::addEventListener(const string& event, const Callback& callback) const
{
	auto *observer = new SPObserver(event, callback);
	this->observers->push_back(observer);

}

SPObservable::~SPObservable()
{
	//dtor
}

}
