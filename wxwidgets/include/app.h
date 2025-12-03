#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SpacifyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class SpacifyFrame : public wxFrame
{
    public:
        SpacifyFrame();
};