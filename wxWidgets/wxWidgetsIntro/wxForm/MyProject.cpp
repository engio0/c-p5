///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 13 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProject.h"

///////////////////////////////////////////////////////////////////////////

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	menubarMain = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* menuItemExit;
	menuItemExit = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuItemExit );

	wxMenuItem* menuItemOpen;
	menuItemOpen = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuItemOpen );

	menubarMain->Append( menuFile, wxT("File") );

	menuEdit = new wxMenu();
	wxMenuItem* menuItemGet;
	menuItemGet = new wxMenuItem( menuEdit, wxID_ANY, wxString( wxT("Get") ) , wxEmptyString, wxITEM_NORMAL );
	menuEdit->Append( menuItemGet );

	menubarMain->Append( menuEdit, wxT("Edit") );

	menuHelp = new wxMenu();
	wxMenuItem* menuItemAbout;
	menuItemAbout = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	menuHelp->Append( menuItemAbout );

	menubarMain->Append( menuHelp, wxT("Help") );

	this->SetMenuBar( menubarMain );


	this->Centre( wxBOTH );
}

MyFrame::~MyFrame()
{
}
