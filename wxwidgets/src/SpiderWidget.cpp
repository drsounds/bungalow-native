//
// Created by Alexander Forselius on 2025-12-03.

#include "SpiderWidget.h"

#include "WindowElement.h"
#include "Skin.h"

SpiderWidget::SpiderWidget(wxWindow *parent,
                wxWindowID winid,
                const wxString& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = SWS_DEFAULT_STYLE,
                const wxValidator& val = wxDefaultValidator,
                const wxString& name = "MySpecialWidget")
{
    this->Init();

    this->Create(parent, winid, label, pos, size, style, val, name);
}

bool SpiderWidget::Create(wxWindow *parent,
            wxWindowID winId,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = SWS_DEFAULT_STYLE,
            const wxValidator& val = wxDefaultValidator,
            const wxString& name = "Spider")
{
    this->gc = new spider::platform::wxwidgets::WxWidgetsGraphicsContext(this);
    this->SetBackgroundColour(wxColour(0, 0, 0));
    this->windowElement = new spider::WindowElement(gc);
    this->windowElement->skin = new spider::Skin("skin.png");
    Bind(wxEVT_PAINT, &SpiderWidget::OnPaint, this);
    Bind(wxEVT_SIZE, &SpiderWidget::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &SpiderWidget::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &SpiderWidget::OnLeftUp, this);
    return FALSE;
}

void SpiderWidget::OnLeftUp(wxMouseEvent& event) {
    this->windowElement->mouseUp(event.GetX(), event.GetY());
}

void SpiderWidget::OnSize(wxSizeEvent& event)
{
    this->windowElement->resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void SpiderWidget::OnLeftDown(wxMouseEvent& event) {
    this->windowElement->mouseDown(1, event.GetX(), event.GetY());
}

wxSize SpiderWidget::DoGetBestSize()
{
    // we need to calculate and return the best size of the widget...
    return wxSize(100, 100);
}

void SpiderWidget::OnPaint(wxPaintEvent& event) {
    // draw the widget on a wxDC...
}
