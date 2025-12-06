#ifndef OBSERVER_H
#define OBSERVER_H
#include "libspider.h"

namespace spider {
    class SPNode;
    class SPObserver {
        string m_event;
        SPCallback m_callback;
    public:
        string getEvent() {
            return this->m_event;
        }
        SPCallback getCallback() const {
            return this->m_callback;
        }
        SPObserver(const string& event, const SPCallback& callback) {
            this->m_event = event;
            this->m_callback = callback;
        }
        ~SPObserver() = default;
    };
}
#endif // OBSERVER_H
