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
#include "SPClassicSkin.h"
#include "WxWidgetsGraphicsContext.h"
#include <wx/process.h>

wxIMPLEMENT_APP(SpacifyApp);

bool SpacifyApp::OnInit(){
    if( !wxApp::OnInit() )
        return false;    
    wxProcess *muxprocess;
    wxString command = wxString("bash ../resources/app/start.sh");
    pythonProcess = new wxProcess(this);
    pythonPid = wxExecute(command, wxEXEC_SHOW_CONSOLE, pythonProcess);
    this->m_space = new space::Space();
    this->m_frame = new SpaceFrame(this, this->m_space);
    space::platform::wxwidgets::WxWidgetsGraphicsContext *gc = new space::platform::wxwidgets::WxWidgetsGraphicsContext(this->m_frame);
    this->m_space->setGraphicsContext(gc);
    gc->setWidget(this->m_frame->getSpaceWidget());
    space::SPSkin *skin = new space::SPClassicSkin();
    this->m_windowElement = new space::SPWindowElement(this->m_space, skin);
    this->m_windowElement->setColorScheme(SP_COLOR_SCHEME_LIGHT);
    this->m_frame->setWindowElement(this->m_windowElement);
    this->m_frame->setSpace(m_space);
    this->m_windowElement->setSpace(m_space);
    this->m_space->addWindow(this->m_windowElement);
    this->m_main = new space::MainElement(this->m_windowElement);
    this->m_main->setId("main");
    this->m_main->setTintColor(new space::SPColor(100, 127, 255, 127));
    this->m_windowElement->appendChild(this->m_main);
    this->m_windowElement->pack();
    this->m_frame->Show(true);
    this->m_frame->getSpaceWidget()->Show();
    return true;
}
