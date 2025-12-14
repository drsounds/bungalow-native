#ifndef OBSERVER_H
#define OBSERVER_H
#include "libspace.h"

namespace space {
    class SPNode;
    class SPObserver {
        string m_event;
        SPCallback m_callback;
        SPElement* m_node;
    	SPElement *m_sender;
    public:
        SPElement* getNode() const {
            return this->m_node;
        }
        string getEvent() {
            return this->m_event;
        }
        SPCallback getCallback() const {
            return this->m_callback;
        }
        SPObserver(const string& event, const SPCallback& callback, SPElement* node, SPElement *sender) {
            this->m_event = event;
            this->m_callback = callback;
            this->m_node = node;
        	this->m_sender = sender;
        }
        ~SPObserver() = default;
    };
}
#endif // OBSERVER_H
