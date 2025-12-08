//
// Created by Alexander Forselius on 2025-12-03.
//

#ifndef SPACIFYCLIENT_APP_H
#define SPACIFYCLIENT_APP_H
#include <boost/json/string.hpp>
#include <string>

#include "SPObservable.h"

#include <queue>

using namespace std;

namespace space
{
    class SPWindowElement;
    class SPEvent;
    class SPSkin;
    class SPGraphicsContext;
    class Space : public SPObservable
    {
    protected:
        SPGraphicsContext *m_graphicsContext;
        vector<SPWindowElement *> *m_windows;
        queue<SPEvent> *m_events;
        queue<SPMessage> *m_messages;
    public:
        vector<SPWindowElement *> *getWindows() {
            return this->m_windows;
        }
        queue<SPEvent> *getEvents() {
            return this->m_events;
        }
        queue<SPMessage> *getMessages() {
            return this->m_messages;
        }
        void setWindows(vector<SPWindowElement *> *value) {
            this->m_windows = value;
        }
        void addWindow(SPWindowElement *window);
        SPGraphicsContext *getGraphicsContext()
        {
            return this->m_graphicsContext;
        }
        void setGraphicsContext(SPGraphicsContext *value) {
            this->m_graphicsContext = value;
        }
        virtual void notify(const string& event, SPObject* sender, SPEventArgs* data) override;
        Space();
        SPWindowElement * createWindow(SPSkin *skin);
        SPMessage dequeueNextMessage();
        void postMessage(const SPMessage& message) const;
        void processEvent(const SPEvent& event) const;
        void processMessage(const SPMessage& message) const;
    };
}

#endif //SPACIFYCLIENT_APP_H