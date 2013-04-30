; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPSCFMThread
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VisualPSD.h"
LastPage=0

ClassCount=12
Class1=CVisualPSDApp
Class2=CVisualPSDDoc
Class3=CVisualPSDView
Class4=CMainFrame
Class12=CPSCFMThread

ResourceCount=7
Resource1=IDR_THEME_MENU (English (U.S.))
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CWorkspaceBar
Class7=CWorkspaceBar2
Resource3=IDD_VISUALPSD_FORM
Resource4=IDD_ABOUTBOX
Resource5=IDR_CONTEXT_MENU (English (U.S.))
Resource6=IDR_PASTE_MENU (English (U.S.))
Class8=CMyEdit
Class9=CPSDisasmThread
Class10=CMyRichEditCtrl
Class11=CPSIA32Thread
Resource7=IDR_MAINFRAME (English (U.S.))

[CLS:CVisualPSDApp]
Type=0
HeaderFile=VisualPSD.h
ImplementationFile=VisualPSD.cpp
Filter=N
LastObject=CVisualPSDApp

[CLS:CVisualPSDDoc]
Type=0
HeaderFile=VisualPSDDoc.h
ImplementationFile=VisualPSDDoc.cpp
Filter=N

[CLS:CVisualPSDView]
Type=0
HeaderFile=VisualPSDView.h
ImplementationFile=VisualPSDView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_RICHEDIT_TEXT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=VisualPSD.cpp
ImplementationFile=VisualPSD.cpp
Filter=D
LastObject=IDC_ABOUT_EDIT
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_COMPANY_URL,button,1342242816
Control6=IDC_ABOUT_EDIT,edit,1350637636

[CLS:CWorkspaceBar]
Type=0
HeaderFile=WorkspaceBar.h
ImplementationFile=WorkspaceBar.cpp
Filter=W

[CLS:CWorkspaceBar2]
Type=0
HeaderFile=WorkspaceBar2.h
ImplementationFile=WorkspaceBar2.cpp
Filter=W

[CLS:COutputBar]
Type=0
HeaderFile=OutputBar.h
ImplementationFile=OutputBar.cpp
Filter=W

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE

[DLG:IDD_VISUALPSD_FORM]
Type=1
Class=CVisualPSDView
ControlCount=4
Control1=IDC_EDIT_DUMP,edit,1084297284
Control2=IDC_EDIT_TEXT,edit,1084297284
Control3=IDC_RICHEDIT_DUMP,RICHEDIT,1344344132
Control4=IDC_RICHEDIT_TEXT,RICHEDIT,1344344132

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_APPLOOK_2000
Command12=ID_VIEW_APPLOOK_XP
Command13=ID_VIEW_APPLOOK_2003
Command14=ID_VIEW_APPLOOK_VS2005
Command15=ID_VIEW_APPLOOK_WIN_XP
Command16=ID_VIEW_APPLOOK_2007
Command17=ID_VIEW_APPLOOK_2007_1
Command18=ID_VIEW_APPLOOK_2007_2
Command19=ID_VIEW_APPLOOK_2007_3
Command20=ID_VIEW_APPLOOK_VS2008
Command21=ID_VIEW_APPLOOK_VS2010
Command22=ID_VIEW_APPLOOK_2010_1
Command23=ID_VIEW_APPLOOK_2010_2
Command24=ID_VIEW_APPLOOK_2010_3
Command25=ID_VIEW_APPLOOK_WIN7
Command26=ID_VIEW_APPLOOK_VS2012_LIGHT
Command27=ID_VIEW_APPLOOK_VS2012_DARK
Command28=ID_APP_ABOUT
CommandCount=28

[MNU:IDR_CONTEXT_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
CommandCount=3

[MNU:IDR_PASTE_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_PASTE
Command2=ID_EDIT_PASTE_SPECIAL
CommandCount=2

[MNU:IDR_THEME_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_APPLOOK_2007
Command2=ID_VIEW_APPLOOK_2007_1
Command3=ID_VIEW_APPLOOK_2007_2
Command4=ID_VIEW_APPLOOK_2007_3
Command5=ID_VIEW_APPLOOK_2010_1
Command6=ID_VIEW_APPLOOK_2010_2
Command7=ID_VIEW_APPLOOK_2010_3
Command8=ID_VIEW_APPLOOK_WIN7
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CMyEdit]
Type=0
HeaderFile=MyEdit.h
ImplementationFile=MyEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=CMyEdit
VirtualFilter=WC

[CLS:CPSDisasmThread]
Type=0
HeaderFile=PSDisasmThread.h
ImplementationFile=PSDisasmThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CPSDisasmThread

[CLS:CMyRichEditCtrl]
Type=0
HeaderFile=MyRichEditCtrl.h
ImplementationFile=MyRichEditCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
LastObject=CMyRichEditCtrl
VirtualFilter=WC

[CLS:CPSIA32Thread]
Type=0
HeaderFile=PSIA32Thread.h
ImplementationFile=PSIA32Thread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CPSIA32Thread

[CLS:CPSCFMThread]
Type=0
HeaderFile=PSCFMThread.h
ImplementationFile=PSCFMThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CPSCFMThread

