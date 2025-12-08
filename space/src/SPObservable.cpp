#include "SPObservable.h"

#include "libspace.h"
#include "SPObject.h"
#include "SPObserver.h"
#include "SPEventArgs.h"

#include "SPNode.h"
#include "SPElement.h"

#include <functional>
#include <type_traits>

namespace space {
	class SPNode;

	SPObservable::SPObservable()
{
	//ctor
	this->observers = new list<SPObserver *>;
}

void SPObservable::dispatchEvent(const string& event, SPEventArgs* args, SPObject* sender) const
{
	this->notify(event, sender, args);
}

void SPObservable::notify(const string& evt, SPObject *sender, SPEventArgs *data) const
{
	for(auto observer : *this->observers) {
		string t = observer->getEvent();
		if(t == (evt)) {
			SPCallback cb = observer->getCallback();
			SPElement *elm = observer->getNode();
			std::invoke(cb, observer->getNode(), sender, data);
		}
	}
}
void SPObservable::addEventListener(const string& event, const SPCallback& callback, SPElement *node) const
{
	auto *observer = new SPObserver(event, callback, node);
	this->observers->push_back(observer);

}

SPObservable::~SPObservable()
{
	//dtor
}

}
