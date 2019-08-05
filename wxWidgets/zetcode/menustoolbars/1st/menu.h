#pragma once
#include <wx/wx.h>

class SimpleMenu : public wxFrame
{
public:
    SimpleMenu(const wxString &title);
    void OnQuit(wxCommandEvent &event);

private:
    wxMenuBar *menubar;
    wxMenu *file;
};
