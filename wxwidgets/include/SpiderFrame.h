#ifndef SPIDER_FRAME_H
#define SPIDER_FRAME_H
#include "SPWindowElement.h"

#include "SPWindow.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderApp;

class SpiderWidget;

namespace spider
{
    class SPObject;
    class Spider;
    class SPWindowElement;
}

class SpiderFrame : public wxFrame
{
protected:
    spider::Spider *m_spider;
    spider::SPWindowElement* m_windowElement;
    SpiderWidget *m_spiderWidget;
    wxApp* m_app;

public:
    void setSpider(spider::Spider *spider) {
        this->m_spider = spider;
    }
    spider::Spider *getSpider() {
        return this->m_spider;
    }
    SpiderWidget *getSpiderWidget() {
        return this->m_spiderWidget;
    }
    spider::SPWindowElement *getWindowElement() {
        return this->m_windowElement;
    }
    void setWindowElement(spider::SPWindowElement *value) {
        this->m_windowElement = value;
    }
    SpiderFrame(wxApp *app);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    wxApp *getApp() const { return m_app; }
};

#endif