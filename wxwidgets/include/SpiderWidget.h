#ifndef SPIDERWIDGET_H
#define SPIDERWIDGET_H
#include <wx/wx.h>

#include "SPObject.h"
#include "Spider.h"
#include "libspider.h"

enum MySpecialWidgetStyles
{
    SWS_LOOK_CRAZY = 1,
    SWS_LOOK_SERIOUS = 2,
    SWS_SHOW_BUTTON = 4,

    SWS_DEFAULT_STYLE = (SWS_SHOW_BUTTON|SWS_LOOK_SERIOUS)
};
namespace spider
{
    class Spider;
    class SPWindowElement;
}
class SpiderFrame;
class SpiderWidget : public wxControl
{
    spider::Spider *m_spider;
    SpiderFrame* m_frame;

    int m_mouseX = 0;
    int m_mouseY = 0;

    virtual wxSize DoGetBestSize();

    void OnPaint(wxPaintEvent&);

public:
    void setSpider(spider::Spider *spider) {
        this->m_spider = spider;
    }
    spider::Spider *getSpider() {
        return this->m_spider;
    }
    wxDECLARE_DYNAMIC_CLASS(SpiderWidget);
	wxSize DoGetBestSize() const;
    void OnMouseMove(wxMouseEvent& event);
    void Init();
    SpiderWidget()
    {
        this->m_spider = nullptr;
        this->m_frame = nullptr;
    }
    SpiderWidget(
        wxWindow *parent,
        wxWindowID winId,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = SWS_DEFAULT_STYLE,
        const wxValidator& val = wxDefaultValidator,
        const wxString& name = "MySpecialWidget"
    );

    bool Create(
        wxWindow *parent,
        wxWindowID winId,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = SWS_DEFAULT_STYLE,
        const wxValidator& val = wxDefaultValidator,
        const wxString& name = "Spider"
    );
    void OnLeftClick(wxCommandEvent& event);
    void OnRightClick(wxCommandEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);

    // accessors...
    wxDECLARE_EVENT_TABLE();

};

#endif