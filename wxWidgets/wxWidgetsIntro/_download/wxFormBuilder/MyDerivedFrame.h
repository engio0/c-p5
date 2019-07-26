#pragma once

#include "MyProject.h"

class MyDerivedFrame : public MyFrame
{
public:
    MyDerivedFrame(wxWindow* parent=NULL); // constructor with a  NULL parameter as frame parent 
                                           // this means it has no parent
    virtual void OnOpen( wxCommandEvent& event );
    virtual void OnExit( wxCommandEvent& event );
    virtual void OnPreferences( wxCommandEvent& event );
    virtual void OnAbout( wxCommandEvent& event );
};