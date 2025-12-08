#ifndef SPACE_APP_H
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpaceFrame;

namespace space
{
    class Space;
    class SPWindowElement;
    class MainElement;
}


class SpacifyApp : public wxApp
{
protected:
    space::Space* m_space;
    space::SPWindowElement *m_windowElement;
    SpaceFrame* m_frame;
    space::MainElement* m_main;
public:
    virtual bool OnInit() override;
};

#endif