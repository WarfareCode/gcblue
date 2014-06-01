// precompiled headers are only used for WIN32
#ifdef WIN32
#pragma warning (disable : 4312) 
#pragma warning (disable : 4996) // 'strdup' was declared deprecated
#include "wx/wxprec.h"      // wxwindows precompiled / standard headers, defines WX_PRECOMP
#include "wx/msw/private.h" // for MS Windows specific definitions

#ifdef _DEBUG
// for memory leak reporting
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

#endif // #ifdef WIN32
