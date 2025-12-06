//
// Created by Alexander Forselius on 2025-12-03.
//

#include "WxGraphicsContext.h"

#include "SPWindowElement.h"

#include "SpiderFrame.h"

using namespace spider::platform::wxwidgets;

WxGraphicsContext::WxGraphicsContext(SpiderFrame* frame) : SPGraphicsContext(frame->getSpider())
{
    this->m_frame = frame;
}

WxGraphicsContext::WxGraphicsContext()
{
}

WxGraphicsContext::~WxGraphicsContext() {
}

void WxGraphicsContext::DrawLine(float x1, float y1, float x2, float y2) {
    if (m_dc) {
        m_dc->DrawLine(x1, y1, x2, y2);
    }
}

void WxGraphicsContext::DrawRectangle(float x, float y, float width, float height) {
    if (m_dc) {
        m_dc->DrawRectangle(x, y, width, height);
    }
}

void WxGraphicsContext::DrawEllipse(float x, float y, float width, float height) {
    if (m_dc) {
        m_dc->DrawEllipse(x, y, width, height);
    }
}

void WxGraphicsContext::DrawText(const std::string& text, float x, float y) {
    if (m_dc) {
        m_dc->DrawText(text, x, y);
    }
}

void WxGraphicsContext::SetLineWidth(float width) {
    if (m_dc) {
        m_dc->SetPen(wxPen(m_dc->GetPen().GetColour(), width));
    }
}

void WxGraphicsContext::SetFillColor(int r, int g, int b, int a) {
    if (m_dc) {
        m_dc->SetBrush(wxBrush(wxColour(r, g, b, a)));
    }
}

void WxGraphicsContext::SetStrokeColor(int r, int g, int b, int a) {
    if (m_dc) {
        m_dc->SetPen(wxPen(wxColour(r, g, b, a)));
    }
}

void WxGraphicsContext::BeginPath() {
    // wxWidgets doesn't have direct path API
}

void WxGraphicsContext::ClosePath() {
    // wxWidgets doesn't have direct path API
}

void WxGraphicsContext::Fill() {
    // Implementation depends on specific needs
}

void WxGraphicsContext::Stroke() {
    // Implementation depends on specific needs
}


