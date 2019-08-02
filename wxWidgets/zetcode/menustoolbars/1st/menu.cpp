#include "menu.h"

SimpleMenu::SimpleMenu(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280,180))
{
    menubar = new wxMenuBar;
}
