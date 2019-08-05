#include "toolbars.h"
#include <wx/image.h>

Toolbar::Toolbar(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(320,250))
{
    wxImage::AddHandler(new wxPNGHandler);

    wxBitmap exit(wxT("./exit.png"), wxBITMAP_TYPE_PNG);
    wxBitmap newb(wxT("./file_yellow_empty_new.png"));
    wxBitmap open(wxT("./file_yellow_open.png"));
    wxBitmap save(wxT("./file_yellow_save.png"));
}
