#include "message.h"

#include <wx/datetime.h>

wxString GetTimeAsString()
{
    auto time = wxDateTime::Now();
    return time.FormatISOCombined('\n');
}
