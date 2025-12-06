//
// Created by Alexander Forselius on 2025-12-03.
//

#ifndef SPACIFYCLIENT_APP_H
#define SPACIFYCLIENT_APP_H
#include <boost/json/string.hpp>
#include <string>

#include "SPObservable.h"

using namespace std;

namespace spider
{
    class SPWindowElement;
    class SPEvent;
    class SPGraphicsContext;
    class Spider : public SPObservable
    {
    protected:
        SPGraphicsContext *m_graphicsContext;
        vector<SPWindowElement *> *m_windows;
        queue<SPEvent> *m_events;
        queue<SPMessage> *m_messages;

    public:
        SPGraphicsContext *getGraphicsContext()
        {
            return this->m_graphicsContext;
        }
        explicit Spider(SPGraphicsContext *graphicsContext);
        Spider();
        SPWindowElement * createWindow();
        SPMessage dequeueNextMessage();
        void postMessage(const SPMessage& message) const;
        void processEvent(const SPEvent& event) const;
        void processMessage(const SPMessage& message) const;
    };
}

#endif //SPACIFYCLIENT_APP_H