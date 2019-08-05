#pragma once
#include <wx/wx.h>
#include <wx/toolbar.h>

class Toolbar : public wxFrame
{
    wxToolBar *toolbar1;
    wxToolBar *toolbar2;

public:
    Toolbar(const wxString &title);
    void OnQuit(wxCommandEvent &event);
};
