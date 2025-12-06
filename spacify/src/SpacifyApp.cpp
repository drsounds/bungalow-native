//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"

#include "SpiderFrame.h"
#include "MainElement.h"

bool SpacifyApp::OnInit()
{
     auto *window = new spider::SPWindowElement(this->m_spider);
     auto *main = new spider::MainElement(window);
     auto *frame = new SpiderFrame(this, window);
     SetTopWindow(frame);
     frame->Show(true);
     return true;
}
