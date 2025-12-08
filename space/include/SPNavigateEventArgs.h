//
// Created by Alexander Forselius on 2025-12-08.
//

#ifndef SPACIFYCLIENT_SPNAVIGATEEVENTARGS_H
#define SPACIFYCLIENT_SPNAVIGATEEVENTARGS_H

#include "SPEventArgs.h"

namespace space
{
    class SPObject;
    class SPNavigateEventArgs : public SPEventArgs
    {
    public:
        explicit SPNavigateEventArgs(string url);
        virtual ~SPNavigateEventArgs();
        string getUrl() {
            return this->url;
        }
        private:
        string url;
    };
} // space

#endif //SPACIFYCLIENT_SPNAVIGATEEVENTARGS_H