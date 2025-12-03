#include <wx/wx.h>

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
    class WindowElement;
}
class SpiderWidget : public wxControl
{
    spider::platform::wxwidgets::WxWidgetsGraphicsContext *gc;
public:
    SpiderWidget();

    SpiderWidget(
        wxWindow *parent,
        wxWindowID winid,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = SWS_DEFAULT_STYLE,
        const wxValidator& val = wxDefaultValidator,
        const wxString& name = "MySpecialWidget"
    );

    bool Create(
        wxWindow *parent,
        wxWindowID winid,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = SWS_DEFAULT_STYLE,
        const wxValidator& val = wxDefaultValidator,
        const wxString& name = "Spider"
    );

    // accessors...

protected:

    void Init();

    virtual wxSize DoGetBestSize();

    void OnPaint(wxPaintEvent&);

private:
    spider::WindowElement *windowElement;
    wxDECLARE_DYNAMIC_CLASS(SpiderWidget);
    wxDECLARE_EVENT_TABLE();
};