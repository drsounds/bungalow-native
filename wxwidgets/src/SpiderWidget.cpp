//
// Created by Alexander Forselius on 2025-12-03.

#include "SpiderWidget.h"
#include "SpiderFrame.h"
#include "SPMouseEventArgs.h"
#include "SPWindowElement.h"
#include "WxGraphicsContext.h"
#include "Spider.h"


BEGIN_EVENT_TABLE(SpiderWidget, wxControl)
    EVT_PAINT(SpiderWidget::OnPaint)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(SpiderWidget, wxControl);

SpiderWidget::SpiderWidget(wxWindow *parent,
                           wxWindowID winId,
                           const wxString& label,
                           const wxPoint& pos,
                           const wxSize& size,
                           long style,
                           const wxValidator& val,
                           const wxString& name )
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
            const wxString& name )
{
    this->SetBackgroundColour(wxColour(255, 255, 255, 1));
    Bind(wxEVT_PAINT, &SpiderWidget::OnPaint, this);
    Bind(wxEVT_SIZE, &SpiderWidget::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &SpiderWidget::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &SpiderWidget::OnLeftUp, this);
    Bind(wxEVT_MOTION, &SpiderWidget::OnMouseMove, this);
    Bind(wxEVT_COMMAND_LEFT_CLICK, &SpiderWidget::OnLeftClick, this);
    return FALSE;
}

void SpiderWidget::OnLeftClick(wxCommandEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, this->m_mouseX, this->m_mouseY);
    const spider::SPEvent evt("click", args, nullptr);
    this->m_spider->dispatchEvent(
        "click",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnRightClick(wxCommandEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, this->m_mouseX, this->m_mouseY);
    const spider::SPEvent evt("click", args, nullptr);
    this->m_spider->dispatchEvent(
        "click",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnLeftUp(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    const spider::SPEvent evt("mouseup", args, nullptr);
    this->m_spider->dispatchEvent(
        "mouseup",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnRightDown(wxMouseEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->m_spider->dispatchEvent(
        "mousedown",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnSize(wxSizeEvent& event)
{
    this->m_frame->getWindow()->resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void SpiderWidget::OnLeftDown(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->m_spider->dispatchEvent(
        "mousedown",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnRightUp(wxMouseEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mouseup", args, nullptr);
    this->m_spider->dispatchEvent(
        "mouseup",
        args,
        this->m_frame->getWindow()
    );
}

void SpiderWidget::OnMouseMove(wxMouseEvent& event)
{
    this->m_mouseX = event.GetX();
    this->m_mouseY = event.GetY();
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    spider::SPEvent evt("mousemove", args, nullptr);
    this->m_spider->dispatchEvent(
        "mousemove",
        args,
        this->m_frame->getWindow()
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
    wxPaintDC dc(this);
    // draw the widget on a wxDC...
    auto* gc = dynamic_cast<spider::platform::wxwidgets::WxGraphicsContext *>(this->m_frame->getWindow()->createGraphics());
    gc->setDC(&dc);
    this->m_frame->getWindow()->draw(gc, this->GetSize().GetWidth(), this->GetSize().GetHeight());
}
