//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"

#include "MainElement.h"
#include "SPWindowElement.h"
#include "SPSkin.h"
#include "SpaceFrame.h"
#include "MainElement.h"
#include "SPWindowElement.h"
#include "SpaceFrame.h"
#include "Space.h"
#include "SpaceWidget.h"
#include "WxWidgetsGraphicsContext.h"

wxIMPLEMENT_APP(SpacifyApp);

bool SpacifyApp::OnInit(){
    if( !wxApp::OnInit() )
          return false;
    this->m_space = new space::Space();
    this->m_frame = new SpaceFrame(this, this->m_space);
    space::platform::wxwidgets::WxWidgetsGraphicsContext *gc = new space::platform::wxwidgets::WxWidgetsGraphicsContext(this->m_frame);
    gc->setWidget(this->m_frame->getSpaceWidget());
    this->m_space->setGraphicsContext(gc);
     this->m_windowElement = new space::SPWindowElement(this->m_space, new space::SPSkin("/Users/buddhalow/Documents/spacify-client/skin.png"));
     this->m_frame->setWindowElement(this->m_windowElement);
     this->m_frame->setSpace(m_space);
     this->m_windowElement->SPWindow::setSpace(m_space);
     this->m_windowElement->SPElement::setSpace(m_space);
     this->m_windowElement->SPNode::setSpace(m_space);
     this->m_windowElement->setWindow(this->m_windowElement);
     this->m_windowElement->SPWindow::setSpace(this->m_space);
     this->m_main = new space::MainElement(this->m_windowElement, this->m_windowElement);
     this->m_main->setId("main");
     this->m_windowElement->appendChild(this->m_main);
    this->m_windowElement->pack();
     this->m_frame->Show(true);
     this->m_frame->getSpaceWidget()->Show();
     return true;
}
