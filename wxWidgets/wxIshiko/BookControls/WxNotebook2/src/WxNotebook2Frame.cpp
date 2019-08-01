/*
    Copyright (c) 2015 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "WxNotebook2Frame.h"
#include "WindowIDs.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <sstream>

WxNotebook2Frame::WxNotebook2Frame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title), m_pageChangingCount(0)
{
    // Create a top-level panel to hold all the contents of the frame
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the wxNotebook widget and give it a specific window id that
    // will be used to identify this widget in the event table
    wxNotebook* notebook = new wxNotebook(panel, MainContentID);

    // Add 2 pages to the wxNotebook widget
    wxTextCtrl* textCtrl1 = new wxTextCtrl(notebook, wxID_ANY, L"Tab 1 Contents");
    notebook->AddPage(textCtrl1, L"Tab 1");
    wxTextCtrl* textCtrl2 = new wxTextCtrl(notebook, wxID_ANY, L"Tab 2 Contents");
    notebook->AddPage(textCtrl2, L"Tab 2");

    // Create the right-hand side panel, it's simply a textbox
    m_mainContents = new wxTextCtrl(panel, wxID_ANY, L"Main Contents Area");

    // Set up the sizer for the panel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(notebook, 0, wxEXPAND);
    panelSizer->Add(m_mainContents, 1, wxEXPAND);
    panel->SetSizer(panelSizer);

    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->SetMinSize(350, 100);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);
}

// Called when the selected page in the wxNotebook is going to be
// changed. We simply keep a count that we display on the right-hand
// side to show that the function is being called.
// In practice you may not need to write a handler for this event at
// all.
void WxNotebook2Frame::OnPageChanging(wxNotebookEvent& evt)
{
    ++m_pageChangingCount;
    evt.Skip();
}

// Called when the selected page in the wxNotebook has been changed.
// In our example we update the contents of the righ-hand side textbox.
void WxNotebook2Frame::OnPageChanged(wxNotebookEvent& evt)
{
    std::wstringstream contents;	
    switch (evt.GetSelection())
    {
    case 0:
        contents << L"Tab 1 selected, page changed ";
        break;

    case 1:
        contents << L"Tab 2 selected, page changed ";
        break;
    }
    contents << m_pageChangingCount << " times";
    m_mainContents->SetValue(contents.str());
    evt.Skip();
}

// Add the 2 event handlers to the event table. As you can see we use
// the window ID to link the event handlers to the wxNotebook we created.
wxBEGIN_EVENT_TABLE(WxNotebook2Frame, wxFrame)
    EVT_NOTEBOOK_PAGE_CHANGING(MainContentID, WxNotebook2Frame::OnPageChanging)
    EVT_NOTEBOOK_PAGE_CHANGED(MainContentID, WxNotebook2Frame::OnPageChanged)
wxEND_EVENT_TABLE()
