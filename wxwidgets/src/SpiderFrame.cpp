#include "SpiderFrame.h"

#include "SpiderWidget.h"
#include "SPObject.h"


SpiderFrame::SpiderFrame(wxApp *app, spider::SPWindowElement *window)
    : wxFrame(nullptr, wxID_ANY, "Spider", wxDefaultPosition, wxDefaultSize)
{
    this->m_app = app;
    this->m_window = window;

    this->m_spiderWidget = new SpiderWidget(dynamic_cast<wxWindow *>(this), wxID_ANY, "Hello World");
    this->AddChild(this->m_spiderWidget);
}

void SpiderFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void SpiderFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void SpiderFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}