#include "SpaceFrame.h"

#include "SpaceWidget.h"
#include "SPObject.h"
#include "Space.h"
#include "SPWindowElement.h"

#include <stdlib.h>

void SpaceFrame::setWindowElement(space::SPWindowElement* value)
{
    this->m_windowElement = value;
    this->m_windowElement->setAbsoluteBounds({ 0, 0, this->getSpaceWidget()->GetSize().GetWidth(), this->getSpaceWidget()->GetSize().GetHeight() });
}

SpaceFrame::SpaceFrame(wxApp *app, space::Space *space)
    : wxFrame(nullptr, wxID_ANY, "Space", wxDefaultPosition, wxSize(1280, 720), wxFRAME_EX_METAL)
{
    this->m_app = app;
    this->m_space = space;

    this->Bind(wxEVT_SIZE, &SpaceFrame::OnSize, this);

    this->m_spaceWidget = new SpaceWidget(dynamic_cast<wxWindow *>(this), wxID_ANY, "Hello World");
    this->m_spaceWidget->setSpace(this->m_space);
    SetWindowStyle(
        wxNO_BORDER |
        wxFRAME_NO_TASKBAR |
        wxCLIP_CHILDREN
    );
    this->AddChild(this->m_spaceWidget);
}

void SpaceFrame::OnSize(wxSizeEvent& event) {
    this->m_spaceWidget->SetSize(event.GetSize());
    this->m_spaceWidget->OnSize(event);
}

void SpaceFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void SpaceFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void SpaceFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}