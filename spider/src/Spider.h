//
// Created by Alexander Forselius on 2025-12-03.
//

#ifndef SPACIFYCLIENT_APP_H
#define SPACIFYCLIENT_APP_H
#include <boost/json/string.hpp>
#include <string>

#include "WindowElement.h"

using namespace std;

namespace spider
{
    class GraphicsContext;
    struct sp_event
    {
        int type;
        void *data;
    };
    struct sp_message
    {
        string subject_uri;
        string predicate;
        string object_uri;
        void *data;
    };
    class Spider
    {
    protected:
        GraphicsContext *m_graphicsContext;
        vector<WindowElement *> m_windows;
        queue<sp_event> m_events;
        queue<sp_message> *m_messages;

    public:
        GraphicsContext *getGraphicsContext()
        {
            return this->m_graphicsContext;
        }
        Spider(GraphicsContext *graphicsContext);
        WindowElement * createWindow();
        void postMessage(const sp_message&);
        void processEvent(const sp_event&);
        sp_message dequeueNextMessage();
        void dispatchEvent(const sp_event&);
        void processMessage(const sp_message&);


    };
}


#endif //SPACIFYCLIENT_APP_H