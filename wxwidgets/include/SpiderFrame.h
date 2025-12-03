#ifndef SPIDER_FRAME_H
#define SPIDER_FRAME_H
#include "WindowElement.h"
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
    spider::WindowElement* m_window;

public:
    SpiderFrame(SpiderApp *, spider::WindowElement*);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    SpiderApp *getApp() const { return m_app; }
};

#endif