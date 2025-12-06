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

class SpiderApp : public wxApp
{
    spider::Spider* m_spider;
public:
    bool OnInit() override;
    SpiderApp();
    explicit SpiderApp(spider::Spider *);
    SpiderFrame *createWindow(spider::SPWindowElement* window);
    spider::Spider *getSpider() const { return m_spider; }
};

#endif