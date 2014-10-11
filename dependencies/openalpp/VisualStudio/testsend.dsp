# Microsoft Developer Studio Project File - Name="testsend" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=testsend - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testsend.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testsend.mak" CFG="testsend - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testsend - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "testsend - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "testsend - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\bin"
# PROP BASE Intermediate_Dir ".\testsend___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir ".\testsend___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "../include" /I "../../portaudio/pa_common" /ZI /W3 /Od /G6 /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /Fp".\testsend___Win32_Debug/testsend.pch" /Fo".\testsend___Win32_Debug/" /Fd".\testsend___Win32_Debug/" /GZ /c /GX 
# ADD CPP /nologo /MDd /I "../include" /I "../../portaudio/pa_common" /ZI /W3 /Od /G6 /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /Fp".\testsend___Win32_Debug/testsend.pch" /Fo".\testsend___Win32_Debug/" /Fd".\testsend___Win32_Debug/" /GZ /c /GX 
# ADD BASE MTL /nologo /tlb".\testsend___Win32_Debug\testsend.tlb" /win32 
# ADD MTL /nologo /tlb".\testsend___Win32_Debug\testsend.tlb" /win32 
# ADD BASE RSC /l 1053 /d "_DEBUG" 
# ADD RSC /l 1053 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  ccgnu2d.lib wsock32.lib /nologo /out:"..\bin\$(ProjectName)d.exe" /incremental:yes /nodefaultlib:"libcd" /debug /pdb:".\testsend___Win32_Debug\testsend.pdb" /pdbtype:sept /subsystem:console /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  ccgnu2d.lib wsock32.lib /nologo /out:"..\bin\$(ProjectName)d.exe" /incremental:yes /nodefaultlib:"libcd" /debug /pdb:".\testsend___Win32_Debug\testsend.pdb" /pdbtype:sept /subsystem:console /MACHINE:I386

!ELSEIF  "$(CFG)" == "testsend - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\bin"
# PROP BASE Intermediate_Dir ".\testsend___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir ".\testsend___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "../include" /I "../../portaudio/pa_common" /W3 /Ob1 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /GF /Gy /YX /Fp".\testsend___Win32_Release/testsend.pch" /Fo".\testsend___Win32_Release/" /Fd".\testsend___Win32_Release/" /c /GX 
# ADD CPP /nologo /MD /I "../include" /I "../../portaudio/pa_common" /W3 /Ob1 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /GF /Gy /YX /Fp".\testsend___Win32_Release/testsend.pch" /Fo".\testsend___Win32_Release/" /Fd".\testsend___Win32_Release/" /c /GX 
# ADD BASE MTL /nologo /tlb".\testsend___Win32_Release\testsend.tlb" /win32 
# ADD MTL /nologo /tlb".\testsend___Win32_Release\testsend.tlb" /win32 
# ADD BASE RSC /l 1053 /d "NDEBUG" 
# ADD RSC /l 1053 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ccgnu2.lib wsock32.lib /nologo /out:"..\bin\$(ProjectName).exe" /incremental:no /libpath:"..\lib" /nodefaultlib:"libcd" /pdb:".\testsend___Win32_Release\testsend.pdb" /pdbtype:sept /subsystem:console /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ccgnu2.lib wsock32.lib /nologo /out:"..\bin\$(ProjectName).exe" /incremental:no /libpath:"..\lib" /nodefaultlib:"libcd" /pdb:".\testsend___Win32_Release\testsend.pdb" /pdbtype:sept /subsystem:console /MACHINE:I386

!ENDIF

# Begin Target

# Name "testsend - Win32 Debug"
# Name "testsend - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\tests\testsend.cpp
# End Source File
# End Group
# End Target
# End Project

