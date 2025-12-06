//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"

#include "MainElement.h"
#include "SPWindowElement.h"
#include "SPSkin.h"
#include "SpiderFrame.h"
#include "MainElement.h"
#include "SPWindowElement.h"
#include "SpiderFrame.h"
#include "Spider.h"
#include "SpiderWidget.h"
#include "WxGraphicsContext.h"

wxIMPLEMENT_APP(SpacifyApp);

bool SpacifyApp::OnInit(){
    if( !wxApp::OnInit() )
          return false;
    this->m_spider = new spider::Spider();
    this->m_frame = new SpiderFrame(this, this->m_spider);
    spider::platform::wxwidgets::WxGraphicsContext *gc = new spider::platform::wxwidgets::WxGraphicsContext(this->m_frame);

    this->m_spider->setGraphicsContext(gc);
     this->m_windowElement = new spider::SPWindowElement(this->m_spider, new spider::SPSkin("/Users/buddhalow/Documents/spacify-client/skin.png"));
     this->m_frame->setWindowElement(this->m_windowElement);
     this->m_frame->setSpider(m_spider);
     this->m_windowElement->SPWindow::setSpider(m_spider);
     this->m_windowElement->SPElement::setSpider(m_spider);
     this->m_windowElement->SPNode::setSpider(m_spider);
     this->m_windowElement->setWindow(this->m_windowElement);
     this->m_windowElement->SPWindow::setSpider(this->m_spider);
     this->m_main = new spider::MainElement(this->m_windowElement, this->m_windowElement);
     this->m_windowElement->appendChild(this->m_main);
     this->m_frame->Show(true);
     this->m_frame->getSpiderWidget()->Show();
     return true;
}
