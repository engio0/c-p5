#include <wx/wx.h>

class HelloWorldApp : public wxApp
{
    public:
        virtual bool OnInit();
};

IMPLEMENT_APP(HelloWorldApp)

bool HelloWorldApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame*) NULL, -1, _T("Hello wxWidgets World"));
    frame->CreateStatusBar();
    frame->SetStatusText(_T("Hello World"));
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
