#include "SpiderFrame.h"

#include "SpiderWidget.h"
#include "SPObject.h"
#include "Spider.h"

SpiderFrame::SpiderFrame(wxApp *app, spider::Spider *spider)
    : wxFrame(nullptr, wxID_ANY, "Spider", wxDefaultPosition, wxDefaultSize)
{
    this->m_app = app;
    this->m_spider = spider;

    this->Bind(wxEVT_SIZE, &SpiderFrame::OnSize, this);

    this->m_spiderWidget = new SpiderWidget(dynamic_cast<wxWindow *>(this), wxID_ANY, "Hello World");
    this->m_spiderWidget->setSpider(this->m_spider);
    this->AddChild(this->m_spiderWidget);
}

void SpiderFrame::OnSize(wxSizeEvent& event) {
    this->m_spiderWidget->SetSize(event.GetSize());
    this->m_spiderWidget->OnSize(event);
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