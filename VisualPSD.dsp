# Microsoft Developer Studio Project File - Name="VisualPSD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisualPSD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisualPSD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisualPSD.mak" CFG="VisualPSD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisualPSD - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisualPSD - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisualPSD - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VisualPSD - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "HAVE_REMOTE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wpcap.lib packet.lib ws2_32.lib beaengine.lib iphlpapi.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"crt.lib" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VisualPSD - Win32 Release"
# Name "VisualPSD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADE.cpp
# End Source File
# Begin Source File

SOURCE=.\asmserv.cpp
# End Source File
# Begin Source File

SOURCE=.\assembl.cpp
# End Source File
# Begin Source File

SOURCE=.\disasm.cpp
# End Source File
# Begin Source File

SOURCE=.\Hook.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PSCFMAnalyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\PSCFMThread.cpp
# End Source File
# Begin Source File

SOURCE=.\PSDisasmer.cpp
# End Source File
# Begin Source File

SOURCE=.\PSDisasmThread.cpp
# End Source File
# Begin Source File

SOURCE=.\PSFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\PSForwarder.cpp
# End Source File
# Begin Source File

SOURCE=.\PSIA32Recognizer.cpp
# End Source File
# Begin Source File

SOURCE=.\PSIA32Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\PSShellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VisualPSD.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPSD.rc
# End Source File
# Begin Source File

SOURCE=.\VisualPSDAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPSDDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPSDView.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADE.h
# End Source File
# Begin Source File

SOURCE=.\disasm.h
# End Source File
# Begin Source File

SOURCE=.\DoWithAPIHook.h
# End Source File
# Begin Source File

SOURCE=.\Hook.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyEdit.h
# End Source File
# Begin Source File

SOURCE=.\MyMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\MyRichEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\OutputBar.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesViewBar.h
# End Source File
# Begin Source File

SOURCE=.\PSCFMAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\PSCFMThread.h
# End Source File
# Begin Source File

SOURCE=.\PSDisasmer.h
# End Source File
# Begin Source File

SOURCE=.\PSDisasmThread.h
# End Source File
# Begin Source File

SOURCE=.\PSFilter.h
# End Source File
# Begin Source File

SOURCE=.\PSForwarder.h
# End Source File
# Begin Source File

SOURCE=.\PSIA32Recognizer.h
# End Source File
# Begin Source File

SOURCE=.\PSIA32Thread.h
# End Source File
# Begin Source File

SOURCE=.\PSShellcode.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VisualPSD.h
# End Source File
# Begin Source File

SOURCE=.\VisualPSDAboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPSDDoc.h
# End Source File
# Begin Source File

SOURCE=.\VisualPSDView.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\VisualPSD.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisualPSD.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VisualPSDDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\workspace.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\ribbonfilelarge.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\ribbonfilesmall.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\ribbonhomelarge.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\ribbonhomesmall.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\ribbonicons.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\ribbonmain.png
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
