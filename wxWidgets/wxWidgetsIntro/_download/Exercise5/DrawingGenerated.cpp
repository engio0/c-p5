///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  6 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "DrawingGenerated.h"

///////////////////////////////////////////////////////////////////////////

GeneratedDrawingFrame::GeneratedDrawingFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( GeneratedDrawingFrame::OnMouseMove ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( GeneratedDrawingFrame::OnPaint ) );
}

GeneratedDrawingFrame::~GeneratedDrawingFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( GeneratedDrawingFrame::OnMouseMove ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( GeneratedDrawingFrame::OnPaint ) );
	
}
