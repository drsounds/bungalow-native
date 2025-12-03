//
// Created by Alexander Forselius on 2025-12-03.
//

#ifndef SPACIFYCLIENT_APP_H
#define SPACIFYCLIENT_APP_H
#include <boost/json/string.hpp>
#include <string>

using namespace std;

namespace spider
{
    class WindowElement;
    class GraphicsContext;
    class Spider
    {
    protected:
        GraphicsContext *m_graphicsContext;
        vector<WindowElement *> *m_windows;
        queue<SPEvent> *m_events;
        queue<SPMessage> *m_messages;

    public:
        GraphicsContext *getGraphicsContext()
        {
            return this->m_graphicsContext;
        }
        explicit Spider(GraphicsContext *graphicsContext);
        WindowElement * createWindow();
        void postMessage(const SPMessage&);
        void processEvent(const SPEvent&);
        SPMessage dequeueNextMessage();
        void dispatchEvent(const SPEvent&);
        void processMessage(const SPMessage&);
    };
}

#endif //SPACIFYCLIENT_APP_H