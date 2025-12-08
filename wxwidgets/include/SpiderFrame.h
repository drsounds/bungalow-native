#ifndef SPIDER_FRAME_H
#define SPIDER_FRAME_H
#include "SPWindowElement.h"

#include "SPWindow.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderApp;

class SpiderWidget;

namespace space
{
    class SPObject;
    class Spider;
    class SPWindowElement;
}

class SpiderFrame : public wxFrame
{
protected:
    space::Spider *m_spider;
    space::SPWindowElement* m_windowElement;
    SpiderWidget *m_spiderWidget;
    wxApp* m_app;

public:
    void setSpider(space::Spider *spider) {
        this->m_spider = spider;
    }
    space::Spider *getSpider() {
        return this->m_spider;
    }
    SpiderWidget *getSpiderWidget() {
        return this->m_spiderWidget;
    }
    space::SPWindowElement *getWindowElement() {
        return this->m_windowElement;
    }
    void setWindowElement(space::SPWindowElement *value) {
        this->m_windowElement = value;
    }
    SpiderFrame(wxApp *app, space::Spider *spider);
    void OnSize(wxSizeEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    wxApp *getApp() const { return m_app; }
};

#endif