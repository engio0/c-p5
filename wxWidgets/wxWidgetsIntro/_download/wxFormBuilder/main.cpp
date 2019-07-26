#include "MyDerivedFrame.h"
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
    MyDerivedFrame *frame = new MyDerivedFrame(NULL);
    frame->Show(true);
    return true;
}
