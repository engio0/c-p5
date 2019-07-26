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

	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );

	m_menubar1->Append( m_menu1, wxT("File") );

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Get") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem3 );

	m_menubar1->Append( m_menu2, wxT("Edit") );

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem4 );

	m_menubar1->Append( m_menu3, wxT("Help") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );
}

MyFrame::~MyFrame()
{
}
