//
// Created by Alexander Forselius on 2025-12-03.

#include "SpiderWidget.h"

SpiderWidget::SpiderWidget(wxWindow *parent,
                wxWindowID winid,
                const wxString& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = SWS_DEFAULT_STYLE,
                const wxValidator& val = wxDefaultValidator,
                const wxString& name = "MySpecialWidget")
{
    Init();

    Create(parent, winid, label, pos, size, style, val, name);
}

void SpiderWidget::Create(wxWindow *parent,
            wxWindowID winid,
            const wxString& label,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = SWS_DEFAULT_STYLE,
            const wxValidator& val = wxDefaultValidator,
            const wxString& name = wxCollapsiblePaneNameStr)
{

}

wxSize SpiderWidget::DoGetBestSize() {
    // we need to calculate and return the best size of the widget...
}

void SpiderWidget::OnPaint(wxPaintEvent& event) {
    // draw the widget on a wxDC...
}
