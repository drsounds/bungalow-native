#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "libspider.h"

#include <list>
#include <string>
using namespace std;
namespace spider {
    class SPNode;
    class SPEventArgs;
    class SPObserver;
    class SPObject;
    class SPObservable
    {
        public:
            SPObservable();
            void dispatchEvent(const string& event, SPEventArgs *data, SPObject *sender);
            void notify(const string& event, SPObject *sender, SPEventArgs *data) const;
            void addEventListener(const string& event, const SPCallback& callback) const;
            virtual ~SPObservable();
        protected:
            list<SPObserver *> *observers;
        private:
    };
}

#endif // OBSERVABLE_H
