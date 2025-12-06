#ifndef SPIDER_APP_H
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderFrame;

namespace spider
{
    class Spider;
    class SPWindowElement;
    class MainElement;
}


class SpacifyApp : public wxApp
{
protected:
    spider::Spider* m_spider;
    spider::SPWindowElement *m_windowElement;
    SpiderFrame* m_frame;
    spider::MainElement* m_main;
public:
    virtual bool OnInit() override;
};

#endif