#ifndef SPIDER_APP_H
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderFrame;

namespace spider
{
    class Spider;
    class SPWindowElement;
}

class SpacifyApp : public wxApp
{
protected:
    spider::Spider* m_spider;
    SpiderFrame* m_frame;
public:
    virtual bool OnInit() override;
};

#endif