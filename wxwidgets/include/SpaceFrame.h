#ifndef SPACE_FRAME_H
#define SPACE_FRAME_H
#include "SPWindowElement.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpaceApp;

class SpaceWidget;

namespace space
{
    class SPObject;
    class Space;
    class SPWindowElement;
}

class SpaceFrame : public wxFrame
{
protected:
    space::Space *m_space;
    space::SPWindowElement* m_windowElement;
    SpaceWidget *m_spaceWidget;
    wxApp* m_app;
	bool m_leftMouseButtonPressed;
public:
    void setSpace(space::Space *space) {
        this->m_space = space;
    }
    space::Space *getSpace() const {
        return this->m_space;
    }
    SpaceWidget *getSpaceWidget() const {
        return this->m_spaceWidget;
    }
    space::SPWindowElement *getWindowElement() const {
        return this->m_windowElement;
    }
    void setWindowElement(space::SPWindowElement *value);
    SpaceFrame(wxApp *app, space::Space *space);
    void OnSize(wxSizeEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    wxApp *getApp() const { return m_app; }
};

#endif