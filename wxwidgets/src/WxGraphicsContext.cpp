#include "WxGraphicsContext.h"

#include "SPImage.h"
#include "SPInputEventArgs.h"
#include "SPElement.h"
#include "SPWindow.h"
#include "SpiderFrame.h"

namespace spider
{
    namespace platform
    {
        namespace wxwidgets
        {
            WxGraphicsContext::WxGraphicsContext(SpiderFrame *frame) : m_window(nullptr), elements(nullptr),
                                                                       widgets(nullptr),
                                                                       widget(nullptr),
                                                                       m_paintDc(nullptr)
            {
                this->m_frame = frame;
            }

            WxGraphicsContext::WxGraphicsContext() : m_frame(nullptr), m_window(nullptr), elements(nullptr),
                                                     widgets(nullptr),
                                                     widget(nullptr),
                                                     m_paintDc(nullptr)
            {
                this->elements = new map<SPElement*, wxControlBase*>();
                this->widgets = new map<wxControlBase*, SPElement*>();
                this->origo = new wxPoint(0, 0);
            }

            WxGraphicsContext::~WxGraphicsContext()
            {
            }

            // --------------------------------------------------------------
            // Clipping
            // --------------------------------------------------------------


            void WxGraphicsContext::setClip(sp_rectangle rect) const
            {
                this->getPaintDC()->SetClippingRegion(rect.x - this->origo->x, rect.y - this->origo->y, rect.width, rect.height);
            }

            void WxGraphicsContext::declipRect()
            {
                this->getPaintDC()->DestroyClippingRegion();
            }

            // --------------------------------------------------------------
            // Transform
            // --------------------------------------------------------------

            void WxGraphicsContext::setOrigo(const int& x, const int& y)
            {
                this->origo->x = x;
                this->origo->y = y;
            }

            void WxGraphicsContext::restoreOrigo()
            {
                this->origo->x = 0;
                this->origo->y = 0;
            }

            void WxGraphicsContext::drawHTMLText(string html, SPFontStyle* fs, SPColor* color, int x, int y, int w,
                int h)
            {
            }

            // --------------------------------------------------------------
            // Primitives
            // --------------------------------------------------------------

            void WxGraphicsContext::drawLine(int x1, int y1,
                                             int x2, int y2,
                                             SPColor* color) const
            {
                if (!color) return;

                wxPen pen(wxColour(color->getR(),
                                   color->getG(),
                                   color->getB()), 1);
                this->getPaintDC()->SetPen(pen);
            }

            void WxGraphicsContext::drawRectangle(int x1, int y1,
                                                     int x2, int y2,
                                                     SPColor* color) const
            {
                wxPen pen(wxColour(color->getR(),
                                   color->getG(),
                                   color->getB()), 1);
                this->getPaintDC()->SetPen(pen);
                this->getPaintDC()->SetBrush(*wxTRANSPARENT_BRUSH);

                this->getPaintDC()->DrawRectangle(x1 - this->origo->x, y1 - this->origo->y, x2 - x1, y2 - y1);
            }

            void WxGraphicsContext::fillRectangle(int x1, int y1,
                                                     int x2, int y2,
                                                     SPColor* color) const
            {
                if (!color) return;

                wxBrush brush(wxColour(color->getR(),
                                       color->getG(),
                                       color->getB()));
                this->getPaintDC()->SetBrush(brush);

                this->getPaintDC()->DrawRectangle(x1 - this->origo->x, y1 - this->origo->y, x2 - x1, y2 - y1);
            }

            // --------------------------------------------------------------
            // Imaging
            // --------------------------------------------------------------

            SPImage* WxGraphicsContext::loadImage(const std::string& file)
            {
                wxBitmap bmp(file, wxBITMAP_TYPE_ANY);

                if (!bmp.IsOk())
                    return nullptr;

                SPImage* img = new SPImage(bmp.GetWidth(), bmp.GetHeight());
                img->handle = new wxBitmap(bmp);

                return img;
            }

            void WxGraphicsContext::drawImage(SPImage* image,
                                                int x, int y,
                                                int width, int height)
            {
                if (!image || !image->handle) return;

                wxBitmap* bmp = static_cast<wxBitmap*>(image->handle);
                this->getPaintDC()->DrawBitmap(*bmp, wxPoint(x - this->origo->x, y - this->origo->y), true);
            }

            void WxGraphicsContext::drawImagePart(SPImage* image,
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

            void WxGraphicsContext::drawSkinImage(string resourceId, int x, int y, int w, int h)
            {
            }

            // --------------------------------------------------------------
            // Text
            // --------------------------------------------------------------

            sp_rectangle WxGraphicsContext::measureString(std::string text,
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

            void WxGraphicsContext::drawString(std::string text,
                                               SPFontStyle* fs,
                                               SPColor* color,
                                               int x, int y,
                                               int w, int h) const
            {
                if (!color) return;

                wxColour col(color->getR(), color->getG(), color->getB());

                wxFont font(fs->getHeight(),
                            wxFONTFAMILY_DEFAULT,
                            wxFONTSTYLE_NORMAL,
                            wxFONTWEIGHT_NORMAL);

                this->getPaintDC()->SetFont(font);
                this->getPaintDC()->SetTextForeground(col);
                this->getPaintDC()->DrawText(text, this->origo->x - x, this->origo->y - y);
            }

            // --------------------------------------------------------------
            // Invalidation
            // --------------------------------------------------------------

            void WxGraphicsContext::invalidateRegion(spider::sp_rectangle rect)
            {
                this->m_window->RefreshRect(wxRect(this->origo->x + rect.x, this->origo->y + rect.y, rect.width, rect.height));
            }

            // --------------------------------------------------------------
            // Controls (text input)
            // --------------------------------------------------------------

            void WxGraphicsContext::drawControl(std::string control,
                                                SPElement* elm,
                                                int x, int y,
                                                int w, int h) const
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

            void WxGraphicsContext::drawInputElement(SPElement* elm,
                                                     int x, int y,
                                                     int w, int h)
            {
                drawControl("EDIT", elm, x - this->origo->x , y - this->origo->y - y, w, h);
            }

            void WxGraphicsContext::setFontStyle(spider::SPFontStyle* fs) const
            {
                this->getPaintDC()->SetFont(wxFont(fs->getHeight(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            }
        }
    }
} // namespace spider
