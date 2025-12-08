#ifndef SPIDER_APP_H
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderFrame;

namespace space
{
    class Spider;
    class SPWindowElement;
    class MainElement;
}


class SpacifyApp : public wxApp
{
protected:
    space::Spider* m_spider;
    space::SPWindowElement *m_windowElement;
    SpiderFrame* m_frame;
    space::MainElement* m_main;
public:
    virtual bool OnInit() override;
};

#endif