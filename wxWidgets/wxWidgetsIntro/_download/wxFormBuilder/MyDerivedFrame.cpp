#include "MyDerivedFrame.h"

#include <wx/msgdlg.h> // contains declaration of wxMessageBox

MyDerivedFrame::MyDerivedFrame(wxWindow *parent) : MyFrame(parent)
{
}

void MyDerivedFrame::OnOpen( wxCommandEvent& event )
{
    wxMessageBox("OnOpen");
}

void MyDerivedFrame::OnExit( wxCommandEvent& event )
{
    wxMessageBox("OnExit");
}

void MyDerivedFrame::OnPreferences( wxCommandEvent& event )
{
    wxMessageBox("OnPreferences");
}

void MyDerivedFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox("OnAbout");
}
