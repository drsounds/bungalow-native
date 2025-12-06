#include "SpiderFrame.h"

#include "SpiderWidget.h"

SpiderFrame::SpiderFrame(wxApp *app, spider::SPWindowElement *window)
    : wxFrame(nullptr, wxID_ANY, "Spider")
{
    this->m_app = app;
    this->m_window = window;
    auto *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    auto *spider_widget = new SpiderWidget(dynamic_cast<wxWindow *>(this), wxID_ANY, "Hello World");
    spider_widget->Show();
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