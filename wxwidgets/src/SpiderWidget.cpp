//
// Created by Alexander Forselius on 2025-12-03.

#include "SpiderWidget.h"
#include "SpiderFrame.h"
#include "MouseEventArgs.h"
#include "SpiderApp.h"
#include "WindowElement.h"
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
    SpiderApp *app = frame->getApp();
    this->m_spider = app->getSpider();
    this->Create(parent, winId, label, pos, size, style, val, name);
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
    this->SetBackgroundColour(wxColour(0, 0, 0));
    Bind(wxEVT_PAINT, &SpiderWidget::OnPaint, this);
    Bind(wxEVT_SIZE, &SpiderWidget::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &SpiderWidget::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &SpiderWidget::OnLeftUp, this);
    Bind(wxEVT_MOTION, &SpiderWidget::OnMouseMove, this);
    Bind(wxEVT_COMMAND_LEFT_CLICK, &SpiderWidget::OnLeftClick, this);
    return FALSE;
}

void SpiderWidget::OnLeftUp(wxMouseEvent& event) {
    spider::MouseEventArgs *args = new spider::MouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mouseup", args, nullptr);
    this->m_spider->dispatchEvent(
        evt
    );
}

void SpiderWidget::OnSize(wxSizeEvent& event)
{
    this->m_spider->resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void SpiderWidget::OnLeftDown(wxMouseEvent& event) {
    spider::MouseEventArgs *args = new spider::MouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->m_spider->dispatchEvent(
        evt
    );
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
