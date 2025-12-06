//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"

#include "SpiderFrame.h"
#include "MainElement.h"
#include "SPWindowElement.h"
#include "SpiderFrame.h"
#include "Spider.h"
#include "SpiderWidget.h"
#include "WxGraphicsContext.h"

wxIMPLEMENT_APP(SpacifyApp);

SpacifyApp::SpacifyApp()
{
     spider::SPGraphicsContext *gc = new spider::platform::wxwidgets::WxGraphicsContext(this->m_frame);
     this->m_spider = new spider::Spider(gc);
}

SpiderFrame *SpacifyApp::createWindow(spider::SPWindowElement *window)
{
     auto *frame = new SpiderFrame(this, window);
     return frame;
}

bool SpacifyApp::OnInit()
{
     auto *window = new spider::SPWindowElement(this->m_spider);
     auto *main = new spider::MainElement(window);
     auto *frame = new SpiderFrame(this, window);
     SetTopWindow(frame);
     frame->Show(true);
     return true;
}
