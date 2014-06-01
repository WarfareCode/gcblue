#ifndef _GCTYPES_H_
#define _GCTYPES_H_

// could be platform dependent
// these are also defined through windows.h or afxwin.h
// and may lead to duplicate or ambiguous definition problems

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT16
typedef short INT16;
#endif

#ifndef UINT32
typedef unsigned int UINT32;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef ULONG_PTR
typedef unsigned long ULONG_PTR;
#endif

#ifndef WIN32 // to avoid visual 7 error related to redefinition

#ifndef LARGE_INTEGER
typedef int long LARGE_INTEGER;
#endif


#ifndef WCHAR
typedef unsigned int WCHAR;
#endif

#ifndef LONGLONG
typedef unsigned long LONGLONG;
#endif

#endif // WIN32

#endif // _GCTYPES_H_
