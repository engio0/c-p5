#include "message.h"

#include <wx/datetime.h>

wxString GetTimeAsString(void)
{
    wxDateTime dt = wxDateTime::Now();
    return dt.FormatISOCombined();
}
