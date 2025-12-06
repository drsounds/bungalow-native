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
    bool OnInit() override;
    SpacifyApp();

    SpiderFrame* getFrame() const { return m_frame; }
    SpiderFrame *createWindow(spider::SPWindowElement* window);
    spider::Spider *getSpider() const { return m_spider; }
    void setSpider(spider::Spider *spider) { this->m_spider = spider; }
};

#endif