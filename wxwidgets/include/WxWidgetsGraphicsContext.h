
#include <wx/dc.h>

#include "GraphicsContext.h"

class SpiderApp;
class SpiderWidget;

namespace spider
{
  namespace platform
  {
    namespace wxwidgets
    {
      class WxWidgetsGraphicsContext : public GraphicsContext
      {
        SpiderApp *m_app;
      public:
        explicit WxWidgetsGraphicsContext(SpiderApp *app);
        WxWidgetsGraphicsContext();
        virtual ~WxWidgetsGraphicsContext();

        virtual void DrawLine(float x1, float y1, float x2, float y2);
        virtual void DrawRectangle(float x, float y, float width, float height);
        virtual void DrawEllipse(float x, float y, float width, float height);
        virtual void DrawText(const std::string& text, float x, float y);

        virtual void SetLineWidth(float width);
        virtual void SetFillColor(int r, int g, int b, int a);
        virtual void SetStrokeColor(int r, int g, int b, int a);

        virtual void BeginPath() ;
        virtual void ClosePath();
        virtual void Fill();
        virtual void Stroke();
        void setDC(wxDC* dc) {
            m_dc = dc;
        }
        wxDC* getDC() const
        {
            return m_dc;
        }
      private:
        SpiderWidget *widget;
        wxDC* m_dc;
      };
    }
  }
}
