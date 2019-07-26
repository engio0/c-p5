// NOTE: You can use "#pragma once" instead of "#ifndef XYZ" "#define XYZ" "#endif" sequence
//
// This assures that header is included only once in a compilation of a unit

#pragma once

#include <wx/string.h>

wxString GetTimeAsString(void);
