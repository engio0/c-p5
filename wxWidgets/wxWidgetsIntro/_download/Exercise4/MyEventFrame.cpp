#include "MyEventFrame.h"

#include <wx/filedlg.h> // for wxFileDialog
#include <wx/msgdlg.h> // for wxMessageBox

MyEventFrame::MyEventFrame(wxWindow *parent) : MyFrame(parent)
{
}

void MyEventFrame::OnStart( wxCommandEvent& event )
{
    // we access protected members from derived class
    m_buttonOpen->Enable(false);
    m_buttonSave->Enable(false);
}

void MyEventFrame::OnStop( wxCommandEvent& event )
{
    m_buttonOpen->Enable(true);
    m_buttonSave->Enable(true);
}

void MyEventFrame::OnOpen( wxCommandEvent& event )
{
    wxFileDialog openFileDialog(this, "Open file", "", "",
                       "All files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea... (pressed cancel)

    SetTitle(openFileDialog.GetPath());
}

void MyEventFrame::OnSave( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, _("Save txt file"), "", "",
                       "Text files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea... (pressed cancel)

    wxMessageBox(saveFileDialog.GetPath());
}

void MyEventFrame::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() )
    {
        if ( wxMessageBox("Do you really want to quit?",
                          "Please confirm",
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();
            return;
        }
    }
    Destroy();  // you may also do:  event.Skip();
                // since the default event handler does call Destroy(), too

}
