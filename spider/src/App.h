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
    struct sp_message
    {
        string subject_uri;
        string predicate;
        string object_uri;
        void *data;
    };
    class App
    {
    protected:
        vector<WindowElement *> windows;
        queue<sp_message> *messages;
        public:
            App(GraphicsContext *graphicsContext);
            void postMessage(sp_message);
            sp_message dequeueNextMessage();
            void processMessage(const sp_message&);


    };
}


#endif //SPACIFYCLIENT_APP_H