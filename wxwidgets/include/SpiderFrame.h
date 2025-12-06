#ifndef SPIDER_FRAME_H
#define SPIDER_FRAME_H
#include "SPWindowElement.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpiderApp;

namespace spider
{
    class Spider;
}

class SpiderFrame : public wxFrame
{
    spider::Spider *m_spider;
    spider::SPWindowElement* m_window;
    wxApp* m_app;

public:
    spider::Spider* getSpider() const { return m_spider; }
    SpiderFrame(wxApp *app, spider::SPWindowElement*);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    spider::SPWindowElement* getWindow() const { return m_window; }
    wxApp *getApp() const { return m_app; }
};

#endif