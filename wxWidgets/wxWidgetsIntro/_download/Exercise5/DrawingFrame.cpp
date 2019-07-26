#include "DrawingFrame.h"

#include <wx/dcclient.h> // for wxPaintDC
#include <wx/utils.h>  // for wxGetMousePosition


DrawingFrame::DrawingFrame( wxWindow* parent )
:
GeneratedDrawingFrame( parent )
{

}

void DrawingFrame::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(this); // we paint on "this" frame
    // DrawOnDC(dc); - commented just to show that everything is drawn on mouse move event
}

void DrawingFrame::DrawOnDC(wxDC& dc)
{
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear(); // clear background
    
    wxCoord width = 0;
    wxCoord height = 0;
    
    dc.GetSize(&width, &height);

    dc.SetPen(*wxRED_PEN);
    
    wxPoint mousePosition = wxGetMousePosition();
    
    int mousex = mousePosition.x;
    int mousey = mousePosition.y;

    this->ScreenToClient(&mousex, &mousey);

    dc.DrawLine(0, 0, mousex, mousey);
    dc.DrawLine(width, 0, mousex, mousey);
    dc.DrawLine(width, height, mousex, mousey);
    dc.DrawLine(0, height, mousex, mousey);
}

void DrawingFrame::OnMouseMove( wxMouseEvent& event )
{
    //Refresh(); - we don't call refresh to force a paint event
    wxClientDC dc(this);
    DrawOnDC(dc);
}
