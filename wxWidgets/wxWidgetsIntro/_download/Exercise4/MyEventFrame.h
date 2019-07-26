#pragma once

#include "FrameProject.h"

class MyEventFrame : public MyFrame
{
public:
    MyEventFrame(wxWindow *parent=NULL); // constructor
    virtual void OnStart( wxCommandEvent& event );
    virtual void OnStop( wxCommandEvent& event );
    virtual void OnOpen( wxCommandEvent& event );
    virtual void OnSave( wxCommandEvent& event );
    void OnClose(wxCloseEvent& event);
};
