#pragma once
#include <wx/wx.h>
<<<<<<< HEAD

class SubMenu : public wxFrame
{
=======
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
>>>>>>> 4f627e46f3560f5955d056f1e58de48daaac0ff5
};
