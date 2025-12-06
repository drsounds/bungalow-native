//
// Created by Alexander Forselius on 2025-12-03.

#include "SpiderWidget.h"
#include "SpiderFrame.h"
#include "SPMouseEventArgs.h"
#include "SpiderApp.h"
#include "SPWindowElement.h"
#include "../../spider/include/Spider.h"

SpiderWidget::SpiderWidget(wxWindow *parent,
                           wxWindowID winId,
                           const wxString& label,
                           const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxDefaultSize,
                           long style = SWS_DEFAULT_STYLE,
                           const wxValidator& val = wxDefaultValidator,
                           const wxString& name = "MySpecialWidget")
{
    this->Init();
    auto *frame = dynamic_cast<SpiderFrame *>(parent);
    this->m_frame = frame;
    this->Create(parent, winId, label, pos, size, style, val, name);
}

bool SpiderWidget::Create(wxWindow *parent,
            wxWindowID winId,
            const wxString& label,
            const wxPoint& pos,
            const wxSize& size,
            long style,
            const wxValidator& val,
            const wxString& name = "Spider")
{
    this->SetBackgroundColour(wxColour(0, 0, 0));
    Bind(wxEVT_PAINT, &SpiderWidget::OnPaint, this);
    Bind(wxEVT_SIZE, &SpiderWidget::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &SpiderWidget::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &SpiderWidget::OnLeftUp, this);
    Bind(wxEVT_MOTION, &SpiderWidget::OnMouseMove, this);
    Bind(wxEVT_COMMAND_LEFT_CLICK, &SpiderWidget::OnLeftClick, this);
    return FALSE;
}

void SpiderWidget::OnLeftClick(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    const spider::SPEvent evt("click", args, nullptr);
    this->m_spider->dispatchEvent(
        evt
    );
}

void SpiderWidget::OnLeftUp(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    const spider::SPEvent evt("mouseup", args, nullptr);
    this->m_spider->dispatchEvent(
        evt
    );
}

void SpiderWidget::OnSize(wxSizeEvent& event)
{
    this->m_frame->getWindow().resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void SpiderWidget::OnLeftDown(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->m_spider->dispatchEvent(
        evt
    );
}

void SpiderWidget::OnMouseMove(wxMouseEvent& event)
{
}

void SpiderWidget::Init()
{
}

wxSize SpiderWidget::DoGetBestSize()
{
    // we need to calculate and return the best size of the widget...
    return wxSize(100, 100);
}

void SpiderWidget::OnPaint(wxPaintEvent& event) {
    // draw the widget on a wxDC...
}
