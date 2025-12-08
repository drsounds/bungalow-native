#ifndef SPGRAPHICSCONTEXT_H
#define SPGRAPHICSCONTEXT_H
#include <wx/dc.h>
#include <wx/graphics.h>
#include <wx/dcscreen.h>
#include <wx/dcclient.h>
#include <wx/image.h>
#include <wx/dcprint.h>

#include "SPGraphicsContext.h"


class wxControlBase;
class SpiderFrame;
class SpiderWidget;

namespace spider
{
  class SPImage;
  class SPColor;
  namespace platform
  {
    namespace wxwidgets
    {
      class WxWidgetsGraphicsContext : public SPGraphicsContext
      {
        SpiderFrame *m_frame;
        wxWindow *m_window;
        map<SPElement *, wxControlBase *> *elements;
        map<wxControlBase *, SPElement *> *widgets;
        wxPoint *origo = new wxPoint(0, 0);
        SpiderWidget *m_widget;
        wxPaintDC* m_paintDc;
      public:
        WxWidgetsGraphicsContext();
        static wxColor toWxColor(SPColor color);
        static SPColor fromWxColor(wxColour color);
        explicit WxWidgetsGraphicsContext(SpiderFrame*);

        void setFrame(SpiderFrame *frame)
        {
          this->m_frame = frame;
        }
        SpiderFrame *getFrame() const
        {
          return this->m_frame;
        }

        void setWindow(wxWindow *window)
        {
          this->m_window = window;
        }
        wxWindow *getWindow() const
        {
          return this->m_window;
        }
        ~WxWidgetsGraphicsContext() override;
        SPImage *loadImage(const string& bitmap) override;
        void drawImagePart(SPImage *image, int x, int y, int width, int height, int x1, int y1, int x2, int y2) override;
        virtual void drawSkinImage(string resourceId, int x, int y, int w, int h);
        void setClip(sp_rectangle rect) const;
        void declipRect() override;
        void drawLine(int x1, int y1, int w, int h, spider::SPColor color) override;
        void drawImage(SPImage *image, int x1, int y1, int w, int h) override;
        void drawRectangle(int x, int y, int w, int h, spider::SPColor color) override;
        void fillRectangle(int x, int y, int w, int h, spider::SPColor color) override;
        void drawControl(const string& control, SPElement *elm, int x, int y, int w, int h) override;
        void invalidateRegion(sp_rectangle region) override;
        void drawString(const string& text, spider::SPFontStyle fontStyle, spider::SPColor color,int x, int y, int w, int h) override;
        void drawInputElement(SPElement *elm, int x, int y, int w, int h) override;
        void setFontStyle(spider::SPFontStyle *fs) const;
        void setOrigo(const int& x, const int& y) override;
        void restoreOrigo() override;
        int getWidth() override;
        int getHeight() override;
        void drawLinearGradient(const sp_rectangle& rect, const SPGradient& gradient) override;
        void drawHTMLText(const string& html, SPFontStyle fontSize, SPColor color, int x, int y, int w, int h) override;
        sp_rectangle measureString(string text, spider::SPFontStyle *font) const;
        void setPaintDC(wxPaintDC* dc) {
            m_paintDc = dc;
        }
        wxPaintDC* getPaintDC() const
        {
            return m_paintDc;
        }

        SpiderWidget* getWidget() const
        {
          return m_widget;
        }
        void setWidget(SpiderWidget* value)
        {
          this->m_widget = value;
        }

      };
    }
  }
}
#endif