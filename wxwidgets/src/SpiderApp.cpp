#include "SpiderApp.h"

#include "SpiderFrame.h"
#include "Spider.h"
#include "SpiderWidget.h"

wxIMPLEMENT_APP(SpiderApp);

SpiderApp::SpiderApp()
{
    spider::SPGraphicsContext *gc = new spider::platform::wxwidgets::WxGraphicsContext(this);
    this->m_spider = new spider::Spider(gc);
}

SpiderApp::SpiderApp(spider::Spider* spider)
{
    this->m_spider = spider;
}

bool SpiderApp::OnInit()
{
    return true;
}

SpiderFrame *SpiderApp::createWindow(spider::SPWindowElement *window)
{
    auto *frame = new SpiderFrame(this, window);
    return frame;
}
