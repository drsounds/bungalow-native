#ifndef OBSERVER_H
#define OBSERVER_H
#include "libspider.h"
namespace spider {
class Observer {
private:
    string _event;
    sp_callback callback;
public:
    string getEvent() {
        return this->_event;
    }
    sp_callback getCallback() {
        return this->callback;
    }
    Observer(string _event, sp_callback callback) {
        this->callback = callback;
        this->_event = _event;
    }
    ~Observer() {
    }
};
}
#endif // OBSERVER_H
