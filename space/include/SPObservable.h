#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "libspace.h"

#include <list>
#include <string>
using namespace std;
namespace space {
    class SPElement;
    class SPEventArgs;
    class SPObserver;
    class SPObject;
    class SPObservable
    {
        public:
            SPObservable();
            void dispatchEvent(const string& event, SPEventArgs *data, SPObject *sender) const;
            virtual void notify(const string& event, SPObject *sender, SPEventArgs *data) const;
            void addEventListener(const string& event, const SPCallback& callback, SPElement *node) const;
            virtual ~SPObservable();
        protected:
            vector<SPObserver *> *observers;
        private:
    };
}

#endif // OBSERVABLE_H
