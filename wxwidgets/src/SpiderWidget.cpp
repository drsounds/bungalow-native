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
                           const wxString& name ) : wxControl(parent, winId)
{
    this->Init();
    this->Create(parent, winId, label, pos, size, style, val, name);
}


wxSize SpiderWidget::DoGetBestSize() const
{
	// Do not return any arbitrary default value...
	wxASSERT_MSG( m_widget, wxT("myStaticText::DoGetBestSize called before creation") );

	// There is probably a better way than this, but I don't know it.
	// So I use the const_cast to grab a dc that is only used for metrics.
	wxClientDC dc (const_cast<SpiderWidget*> (this));

	wxCoord w = 0;
	wxCoord h = 0;
	dc.GetTextExtent( GetLabel (), &w, &h );

	return wxSize( w, h );
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
    this->getSpider()->dispatchEvent(
        "click",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnRightClick(wxCommandEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, this->m_mouseX, this->m_mouseY);
    const spider::SPEvent evt("click", args, nullptr);
    this->m_spider->dispatchEvent(
        "click",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnLeftUp(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    const spider::SPEvent evt("mouseup", args, nullptr);
    this->getSpider()->dispatchEvent(
        "mouseup",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnRightDown(wxMouseEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->getSpider()->dispatchEvent(
        "mousedown",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnSize(wxSizeEvent& event)
{
    this->m_frame->getWindowElement()->resize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void SpiderWidget::OnLeftDown(wxMouseEvent& event) {
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    spider::SPEvent evt("mousedown", args, nullptr);
    this->getSpider()->dispatchEvent(
        "mousedown",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnRightUp(wxMouseEvent& event)
{
    auto *args = new spider::SPMouseEventArgs(1, event.GetX(), event.GetY());
    spider::SPEvent evt("mouseup", args, nullptr);
    this->getSpider()->dispatchEvent(
        "mouseup",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::OnMouseMove(wxMouseEvent& event)
{
    this->m_mouseX = event.GetX();
    this->m_mouseY = event.GetY();
    auto *args = new spider::SPMouseEventArgs(0, event.GetX(), event.GetY());
    spider::SPEvent evt("mousemove", args, nullptr);
    this->getSpider()->dispatchEvent(
        "mousemove",
        args,
        this->m_frame->getWindowElement()
    );
}

void SpiderWidget::Init()
{
    auto *frame = dynamic_cast<SpiderFrame *>(this->GetParent());
    this->m_frame = frame;
}

wxSize SpiderWidget::DoGetBestSize()
{
    // we need to calculate and return the best size of the widget...
    return wxSize(100, 100);
}

void SpiderWidget::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    int width = this->GetSize().GetWidth();
    int height = this->GetSize().GetHeight();
    // draw the widget on a wxDC...
    auto* gc = dynamic_cast<spider::platform::wxwidgets::WxGraphicsContext *>(this->m_frame->getWindowElement()->createGraphics());
    gc->setFrame(this->m_frame);
    gc->setWindow(this->GetParent());
    gc->setPaintDC(&dc);
	GetClientSize( &width, &height );
    cout << width;
    cout << height;
    this->m_frame->getWindowElement()->draw(gc, width, height);
}
