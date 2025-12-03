//
// Created by Alexander Forselius on 2025-12-03.
//

#include "WxWidgetsGraphicsContext.h"

using namespace spider::platform::wxwidgets;

WxWidgetsGraphicsContext::WxWidgetsGraphicsContext() : m_dc(nullptr) {
}

WxWidgetsGraphicsContext::~WxWidgetsGraphicsContext() {
}

void WxWidgetsGraphicsContext::DrawLine(float x1, float y1, float x2, float y2) {
    if (m_dc) {
        m_dc->DrawLine(x1, y1, x2, y2);
    }
}

void WxWidgetsGraphicsContext::DrawRectangle(float x, float y, float width, float height) {
    if (m_dc) {
        m_dc->DrawRectangle(x, y, width, height);
    }
}

void WxWidgetsGraphicsContext::DrawEllipse(float x, float y, float width, float height) {
    if (m_dc) {
        m_dc->DrawEllipse(x, y, width, height);
    }
}

void WxWidgetsGraphicsContext::DrawText(const std::string& text, float x, float y) {
    if (m_dc) {
        m_dc->DrawText(text, x, y);
    }
}

void WxWidgetsGraphicsContext::SetLineWidth(float width) {
    if (m_dc) {
        m_dc->SetPen(wxPen(m_dc->GetPen().GetColour(), width));
    }
}

void WxWidgetsGraphicsContext::SetFillColor(int r, int g, int b, int a) {
    if (m_dc) {
        m_dc->SetBrush(wxBrush(wxColour(r, g, b, a)));
    }
}

void WxWidgetsGraphicsContext::SetStrokeColor(int r, int g, int b, int a) {
    if (m_dc) {
        m_dc->SetPen(wxPen(wxColour(r, g, b, a)));
    }
}

void WxWidgetsGraphicsContext::BeginPath() {
    // wxWidgets doesn't have direct path API
}

void WxWidgetsGraphicsContext::ClosePath() {
    // wxWidgets doesn't have direct path API
}

void WxWidgetsGraphicsContext::Fill() {
    // Implementation depends on specific needs
}

void WxWidgetsGraphicsContext::Stroke() {
    // Implementation depends on specific needs
}


