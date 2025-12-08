#include "WxWidgetsGraphicsContext.h"

#include "SPImage.h"
#include "SPInputEventArgs.h"
#include "SPElement.h"
#include "SPWindow.h"
#include "SpiderFrame.h"
#include "SpiderWidget.h"

namespace space
{
    namespace platform
    {
        namespace wxwidgets
        {
            WxWidgetsGraphicsContext::WxWidgetsGraphicsContext(SpiderFrame *frame) : WxWidgetsGraphicsContext()
            {
                this->m_frame = frame;
            }

            wxColour WxWidgetsGraphicsContext::toWxColor(SPColor color)
            {
                return wxColour(color.getR(), color.getG(), color.getB(), color.getA());
            }

            SPColor WxWidgetsGraphicsContext::fromWxColor(wxColor color)
            {
                return SPColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
            }

            WxWidgetsGraphicsContext::WxWidgetsGraphicsContext() : m_frame(nullptr), m_window(nullptr), elements(nullptr),
                                                     widgets(nullptr),
                                                     m_widget(nullptr),
                                                     m_paintDc(nullptr)
            {
                this->elements = new map<SPElement*, wxControlBase*>();
                this->widgets = new map<wxControlBase*, SPElement*>();
                this->origo = new wxPoint(0, 0);
            }

            WxWidgetsGraphicsContext::~WxWidgetsGraphicsContext()
            {
            }

            // --------------------------------------------------------------
            // Clipping
            // --------------------------------------------------------------


            void WxWidgetsGraphicsContext::setClip(sp_rectangle rect) const
            {
                this->getPaintDC()->SetClippingRegion(rect.x - this->origo->x, rect.y - this->origo->y, rect.width, rect.height);
            }

            void WxWidgetsGraphicsContext::declipRect()
            {
                this->getPaintDC()->DestroyClippingRegion();
            }

            // --------------------------------------------------------------
            // Transform
            // --------------------------------------------------------------

            void WxWidgetsGraphicsContext::setOrigo(const int& x, const int& y)
            {
                if (this->getPaintDC()->CanUseTransformMatrix())
                {
                    wxAffineMatrix2D matrix{};
                    matrix.Translate(x, y);
                    this->getPaintDC()->SetTransformMatrix(matrix);
                }
                else
                {
                    this->origo->x = x;
                    this->origo->y = y;
                }
            }

            void WxWidgetsGraphicsContext::restoreOrigo()
            {
                if (this->getPaintDC()->CanUseTransformMatrix())
                {
                    this->getPaintDC()->ResetTransformMatrix();
                }
                else
                {
                    this->origo->x = 0;
                    this->origo->y = 0;
                }
            }

            int WxWidgetsGraphicsContext::getWidth()
            {
                if (m_widget == nullptr)
                {
                    return 0;
                }
                return this->m_widget->GetClientSize().GetWidth();
            }

            int WxWidgetsGraphicsContext::getHeight()
            {
                if (m_widget == nullptr)
                {
                    return 0;
                }
                return this->m_widget->GetClientSize().GetHeight();
            }
            void WxWidgetsGraphicsContext::drawHTMLText(const string& html, SPFontStyle fontSize, SPColor color, int x, int y,
                                                        int w, int h)
            {
            }

            // --------------------------------------------------------------
            // Primitives
            // --------------------------------------------------------------

            void WxWidgetsGraphicsContext::drawLine(int x1, int y1,
                                             int x2, int y2,
                                             SPColor color)
            {
                wxPen pen(wxColour(color.getR(),
                                   color.getG(),
                                   color.getB()), 1);
                this->getPaintDC()->SetPen(pen);
                this->getPaintDC()->DrawLine(x1 - this->origo->x, y1 - this->origo->y, x2 - this->origo->x, y2 - this->origo->y);
            }

            void WxWidgetsGraphicsContext::drawRectangle(int x, int y,
                                                     int width, int height,
                                                     SPColor color)
            {
                wxPen pen(wxColour(color.getR(),
                                   color.getG(),
                                   color.getB()), 1);
                this->getPaintDC()->SetPen(pen);
                this->getPaintDC()->SetBrush(*wxTRANSPARENT_BRUSH);

                this->getPaintDC()->DrawRectangle(x - this->origo->x, y - this->origo->y, width - x, height - y);
            }

            void WxWidgetsGraphicsContext::fillRectangle(int x, int y,
                                                     int width, int height,
                                                     SPColor color)
            {
                wxBrush brush(wxColour(color.getR(),
                                       color.getG(),
                                       color.getB()));
                this->getPaintDC()->SetBrush(brush);
                this->getPaintDC()->SetPen(wxPen());

                this->getPaintDC()->DrawRectangle(x - this->origo->x, y - this->origo->y, width, height);
            }

            // --------------------------------------------------------------
            // Imaging
            // --------------------------------------------------------------

            SPImage* WxWidgetsGraphicsContext::loadImage(const std::string& file)
            {
                wxBitmap bmp(file, wxBITMAP_TYPE_ANY);

                if (!bmp.IsOk())
                    return nullptr;

                SPImage* img = new SPImage(bmp.GetWidth(), bmp.GetHeight());
                img->handle = new wxBitmap(bmp);

                return img;
            }

            void WxWidgetsGraphicsContext::drawImage(SPImage* image,
                                                int x, int y,
                                                int width, int height)
            {
                if (!image || !image->handle) return;

                wxBitmap* bmp = static_cast<wxBitmap*>(image->handle);
                this->getPaintDC()->DrawBitmap(*bmp, wxPoint(x - this->origo->x, y - this->origo->y), true);
            }

            void WxWidgetsGraphicsContext::drawImagePart(SPImage* image,
                                                    int left, int top,
                                                    int width, int height,
                                                    int sx, int sy,
                                                    int sw, int sh)
            {
                if (!image || !image->handle) return;

                wxBitmap* bmp = static_cast<wxBitmap*>(image->handle);

                wxBitmap sub = bmp->GetSubBitmap(wxRect(sx, sy, sw, sh));
                this->getPaintDC()->DrawBitmap(sub, wxPoint(left - this->origo->x, top - this->origo->y), true);
            }

            void WxWidgetsGraphicsContext::drawSkinImage(string resourceId, int x, int y, int w, int h)
            {
            }

            void WxWidgetsGraphicsContext::drawLinearGradient(const sp_rectangle& rect, const SPGradient& gradient)
            {
                this->getPaintDC()->SetBrush(
                    wxBrush(
                        WxWidgetsGraphicsContext::toWxColor(
                            gradient.getStart()
                        ),
                        wxTRANSPARENT
                    )
                );
                this->getPaintDC()->GradientFillLinear(
                    wxRect(
                        rect.x,
                        rect.y,
                        rect.width,
                        rect.height
                    ),
                    toWxColor(
                        gradient.getStart()
                    ),
                    toWxColor(
                        gradient.getEnd()
                    ),
                    wxSOUTH
                );
            }

            // --------------------------------------------------------------
            // Text
            // --------------------------------------------------------------

            sp_rectangle WxWidgetsGraphicsContext::measureString(std::string text,
                                                          SPFontStyle* fs) const
            {
                wxFont font(fs->getHeight(),
                            wxFONTFAMILY_DEFAULT,
                            wxFONTSTYLE_NORMAL,
                            wxFONTWEIGHT_NORMAL);

                this->getPaintDC()->SetFont(font);
                wxSize size = this->getPaintDC()->GetTextExtent(text);
                return { size.GetWidth(), size.GetHeight(), size.x, size.y };
            }

            void WxWidgetsGraphicsContext::drawString(const std::string& text,
                                               SPFontStyle fs,
                                               SPColor color,
                                               int x, int y,
                                               int w, int h)
            {
                wxColour col(color.getR(), color.getG(), color.getB());

                wxFont font(fs.getHeight(),
                            wxFONTFAMILY_DEFAULT,
                            wxFONTSTYLE_NORMAL,
                            wxFONTWEIGHT_NORMAL);

                this->getPaintDC()->SetTextForeground(col);
                this->getPaintDC()->DrawText(wxString(text), x - this->origo->x, y - this->origo->y);
            }

            // --------------------------------------------------------------
            // Invalidation
            // --------------------------------------------------------------

            void WxWidgetsGraphicsContext::invalidateRegion(space::sp_rectangle rect)
            {
                this->m_window->RefreshRect(wxRect(this->origo->x + rect.x, this->origo->y + rect.y, rect.width, rect.height));
            }

            // --------------------------------------------------------------
            // Controls (text input)
            // --------------------------------------------------------------

            void WxWidgetsGraphicsContext::drawControl(const std::string& control,
                                                SPElement* elm,
                                                int x, int y,
                                                int w, int h)
            {
                // Only supports text controls (“EDIT”)
                if (elements->count(elm) == 0)
                {
                    wxTextCtrl* ctrl = new wxTextCtrl(
                        this->m_window,
                        wxID_ANY,
                        "",
                        wxPoint(x, y),
                        wxSize(w, h)
                    );

                    (*elements)[elm] = ctrl;

                    ctrl->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent& evt)
                    {
                        elm->notify("enter", elm,
                                    new SPInputEventArgs(evt.GetString().ToStdString()));
                    });
                }
                else
                {
                    (*elements)[elm]->SetSize(x - this->origo->x, y - this->origo->y, w, h);
                }
            }

            void WxWidgetsGraphicsContext::drawInputElement(SPElement* elm,
                                                     int x, int y,
                                                     int w, int h)
            {
                drawControl("EDIT", elm, x - this->origo->x , y - this->origo->y, w, h);
            }

            void WxWidgetsGraphicsContext::setFontStyle(space::SPFontStyle* fs) const
            {
                this->getPaintDC()->SetFont(wxFont(fs->getHeight(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            }
        }
    }
} // namespace space
