#pragma once
#include <wx/wx.h>
#include <wx/menu.h>

class SubMenu : public wxFrame
{
public:
    SubMenu(const wxString &title);
    void OnQuit(wxCommandEvent &event);

private:
    wxMenuBar *menubar;
    wxMenu *file;
    wxMenu *imp;
    wxMenuItem *quit;
};
