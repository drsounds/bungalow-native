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
	this->observers = new vector<SPObserver *>;
}

void SPObservable::dispatchEvent(const string& event, SPEventArgs* args, SPObject* sender)
{
	this->notify(event, sender, args);
}

void SPObservable::notify(const string& evt, SPObject *sender, SPEventArgs *data)
{
	for(auto observer : *this->observers) {
		string t = observer->getEvent();
		if(t == (evt)) {
			SPCallback cb = observer->getCallback();
			SPElement *elm = observer->getNode();
			std::invoke(cb, observer->getNode(), elm, data);
		}
	}
}
void SPObservable::addEventListener(const string& event, const SPCallback& callback, SPElement *node)
{
	auto *observer = new SPObserver(event, callback, node);
	this->observers->push_back(observer);

}

SPObservable::~SPObservable()
{
	//dtor
}

}
