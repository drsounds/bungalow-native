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
    SpiderApp *m_app{};
    spider::SPWindowElement* m_window;

public:
    SpiderFrame(SpiderApp *, spider::SPWindowElement*);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    spider::SPWindowElement* getWindow() const { return m_window; }
    SpiderApp *getApp() const { return m_app; }
};

#endif