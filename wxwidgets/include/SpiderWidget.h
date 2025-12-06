#include <wx/wx.h>

#include "SpiderFrame.h"
#include "WxWidgetsGraphicsContext.h"

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
class SpiderWidget : public wxControl
{
private:
    spider::Spider *m_spider;
    SpiderFrame* m_frame;

    virtual wxSize DoGetBestSize();

    void OnPaint(wxPaintEvent&);

public:
    spider::Spider *getApp()
    {
        return m_spider;
    }
    void OnMouseMove(wxMouseEvent& event);
    void Init();
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
    void OnLeftClick(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnLeftDown(wxMouseEvent& event);

    // accessors...
    wxDECLARE_DYNAMIC_CLASS(SpiderWidget);
    wxDECLARE_EVENT_TABLE();

};