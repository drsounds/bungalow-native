//
// Created by Alexander Forselius on 2025-12-03.
//

#ifndef SPACIFYCLIENT_SPACIFYAPP_H
#define SPACIFYCLIENT_SPACIFYAPP_H
#ifndef SPIDER_APP_H
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "SpiderApp.h"

class SpiderFrame;

namespace spider
{
    class Spider;
    class SPWindowElement;
}

class SpacifyApp : public SpiderApp
{
    spider::Spider* m_spider;
public:
    bool OnInit() override;
};

#endif
#endif //SPACIFYCLIENT_SPACIFYAPP_H