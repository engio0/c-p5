#include <wx/wx.h>
#include "main.h"
#include "button.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Button *btapp = new Button(wxT("Button"));
    btapp->Show(true);

    return true;
}
