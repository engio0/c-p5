#include "MyEventFrame.h"
#include <wx/app.h>
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
DECLARE_APP(MyApp)

IMPLEMENT_APP(MyApp)
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;
    MyEventFrame *frame = new MyEventFrame();
    frame->Show(true);
    return true;
}
