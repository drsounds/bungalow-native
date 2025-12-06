//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"

#include "SPSkin.h"
#include "SpiderFrame.h"
#include "MainElement.h"
#include "SPWindowElement.h"
#include "SpiderFrame.h"
#include "Spider.h"
#include "SpiderWidget.h"
#include "WxGraphicsContext.h"

wxIMPLEMENT_APP(SpacifyApp);

bool SpacifyApp::OnInit()
{
     if( !wxApp::OnInit() )
          return false;
     auto *window = new spider::SPWindowElement(this->m_spider, new spider::SPSkin("/Users/buddhalow/Documents/spacify-client/skin.png"));
     auto *main = new spider::MainElement(window);
     auto *frame = new SpiderFrame(this, window);
     this->m_frame = frame;
     spider::platform::wxwidgets::WxGraphicsContext *gc = new spider::platform::wxwidgets::WxGraphicsContext(this->m_frame);
     this->m_spider = new spider::Spider(gc);
     this->m_frame->Show(true);
     return true;
}
