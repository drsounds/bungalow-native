#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "libspider.h"
#include "SPType.h"
#include "Observer.h"
#include <list>
#include "EventArgs.h"
using namespace std;
namespace spider {
    class Observable
    {
        public:
            Observable();
            void dispatchEvent(const string& event, EventArgs *data, SPType *sender);
            void notify(const string& event, SPType *sender, EventArgs *data) const;
            void addEventListener(const string& event, const sp_callback& e);
            virtual ~Observable();
        protected:
            list<Observer *> *observers;
        private:
    };
}

#endif // OBSERVABLE_H
