#include "GraphicsContext.h"
#include <wx/dc.h>

class SpiderWidget;

namespace spider
{
  namespace platform
  {
    namespace wxwidgets
    {
      class WxWidgetsGraphicsContext : public GraphicsContext
      {
      public:
        WxWidgetsGraphicsContext(SpiderWidget *widget);
        virtual ~WxWidgetsGraphicsContext();

        virtual void DrawLine(float x1, float y1, float x2, float y2) override;
        virtual void DrawRectangle(float x, float y, float width, float height) override;
        virtual void DrawEllipse(float x, float y, float width, float height) override;
        virtual void DrawText(const std::string& text, float x, float y) override;

        virtual void SetLineWidth(float width) override;
        virtual void SetFillColor(int r, int g, int b, int a = 255) override;
        virtual void SetStrokeColor(int r, int g, int b, int a = 255) override;

        virtual void BeginPath() override;
        virtual void ClosePath() override;
        virtual void Fill() override;
        virtual void Stroke() override;

      private:
        SpiderWidget *widget;
        wxDC* m_dc;
      };
    }
  }
}
