#ifndef SPIDER_FRAME_H
#define SPIDER_FRAME_H
#include "SPWindowElement.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderApp;

class SpiderWidget;

namespace spider
{
    class SPObject;
    class Spider;
    class Spider;
}

class SpiderFrame : virtual public wxFrame, public SPObject
{
protected:
    spider::Spider *m_spider;
    spider::SPWindowElement* m_window;
    SpiderWidget *m_spiderWidget;
    wxApp* m_app;

public:
    SpiderWidget *getSpiderWidget() {
        return this->m_spiderWidget;
    }
    SpiderFrame(wxApp *app, spider::SPWindowElement*);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    void setSpider(spider::Spider *spider) {
        this->m_spider = spider;
    }
    spider::Spider *getSpider() {
        return this->m_spider;
    }
    spider::SPWindowElement* getWindow() const { return m_window; }
    wxApp *getApp() const { return m_app; }
};

#endif