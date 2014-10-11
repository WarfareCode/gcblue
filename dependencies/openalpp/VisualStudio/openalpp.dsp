# Microsoft Developer Studio Project File - Name="oalpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=oalpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "oalpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oalpp.mak" CFG="oalpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oalpp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "oalpp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oalpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../lib"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "../include" /ZI /W3 /Od /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "OPENALPP_EXPORTS" /D "WIN32" /D "_MBCS" /GR /YX /Fp".\Debug/openalpp.pch" /Fo".\Debug/" /Fd".\Debug/" /FR /GZ /c /GX 
# ADD CPP /nologo /MDd /I "../include" /ZI /W3 /Od /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "OPENALPP_EXPORTS" /D "WIN32" /D "_MBCS" /GR /YX /Fp".\Debug/openalpp.pch" /Fo".\Debug/" /Fd".\Debug/" /FR /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\..\lib\openalpp.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\..\lib\openalpp.tlb" /win32 
# ADD BASE RSC /l 1053 /d "_DEBUG" 
# ADD RSC /l 1053 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openthreadswin32d.lib alut.lib openal32.lib  winmm.lib  dsound.lib vorbisfile_d.lib ogg_d.lib /nologo /dll /out:"..\bin\$(ProjectName)d.dll" /incremental:yes /debug /pdb:".\..\lib\openalppd.pdb" /pdbtype:sept /subsystem:windows /implib:"../lib/$(ProjectName)d.lib" /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openthreadswin32d.lib alut.lib openal32.lib  winmm.lib  dsound.lib vorbisfile_d.lib ogg_d.lib /nologo /dll /out:"..\bin\$(ProjectName)d.dll" /incremental:yes /debug /pdb:".\..\lib\openalppd.pdb" /pdbtype:sept /subsystem:windows /implib:"../lib/$(ProjectName)d.lib" /MACHINE:I386

!ELSEIF  "$(CFG)" == "oalpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../lib"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "../include" /W3 /Ob1 /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "OPENALPP_EXPORTS" /D "WIN32" /D "_MBCS" /GF /Gy /GR /YX /Fp".\Release/openalpp.pch" /Fo".\Release/" /Fd".\Release/" /c /GX 
# ADD CPP /nologo /MD /I "../include" /W3 /Ob1 /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "OPENALPP_EXPORTS" /D "WIN32" /D "_MBCS" /GF /Gy /GR /YX /Fp".\Release/openalpp.pch" /Fo".\Release/" /Fd".\Release/" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\lib\openalpp.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\lib\openalpp.tlb" /win32 
# ADD BASE RSC /l 1053 /d "NDEBUG" 
# ADD RSC /l 1053 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openthreadswin32.lib alut.lib openal32.lib vorbisfile.lib ogg.lib winmm.lib wsock32.lib dsound.lib /nologo /dll /out:"..\bin\$(ProjectName).dll" /incremental:no /nodefaultlib:"LIBC" /pdb:".\..\lib\openalpp.pdb" /pdbtype:sept /subsystem:windows /implib:"../lib/$(ProjectName).lib" /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openthreadswin32.lib alut.lib openal32.lib vorbisfile.lib ogg.lib winmm.lib wsock32.lib dsound.lib /nologo /dll /out:"..\bin\$(ProjectName).dll" /incremental:no /nodefaultlib:"LIBC" /pdb:".\..\lib\openalpp.pdb" /pdbtype:sept /subsystem:windows /implib:"../lib/$(ProjectName).lib" /MACHINE:I386

!ENDIF

# Begin Target

# Name "oalpp - Win32 Debug"
# Name "oalpp - Win32 Release"
# Begin Group "Source files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\audiobase.cpp
# End Source File
# Begin Source File

SOURCE=..\src\audioconvert.cpp
# End Source File
# Begin Source File

SOURCE=..\src\audioenvironment.cpp
# End Source File
# Begin Source File

SOURCE=..\src\error.cpp
# End Source File
# Begin Source File

SOURCE=..\src\filestream.cpp
# End Source File
# Begin Source File

SOURCE=..\src\filestreamupdater.cpp
# End Source File
# Begin Source File

SOURCE=..\src\groupsource.cpp
# End Source File
# Begin Source File

SOURCE=..\src\listener.cpp
# End Source File
# Begin Source File

SOURCE=..\src\openalpp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\referenced.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sample.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sounddata.cpp
# End Source File
# Begin Source File

SOURCE=..\src\source.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sourcebase.cpp
# End Source File
# Begin Source File

SOURCE=..\src\stream.cpp
# End Source File
# Begin Source File

SOURCE=..\src\streamupdater.cpp
# End Source File
# End Group
# Begin Group "Header files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\openalpp\alpp.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\audiobase.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\audioconvert.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\audioenvironment.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\config.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\error.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\export.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\filestream.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\filestreamupdater.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\groupsource.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\inputdevice.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\listener.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\positionedobject.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\sample.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\sounddata.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\source.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\sourcebase.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\stream.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\streamupdater.h
# End Source File
# Begin Source File

SOURCE=..\include\openalpp\windowsstuff.h
# End Source File
# End Group
# End Target
# End Project

