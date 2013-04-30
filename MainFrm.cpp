// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "VisualPSDView.h"

#include "MainFrm.h"
#include "DoWithAPIHook.h"
#include "MyMessageBox.h"

#include "PSDisasmThread.h"
#include "PSDisasmer.h"
#include "PSFilter.h"
#include "PSForwarder.h"

#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GUI_MESSAGE 0x1060

CMainFrame *pThis;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2012_DARK, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2012_DARK, OnUpdateAppLook)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_COMMAND(ID_VIEW_WORKSPACE2, OnViewWorkspace2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE2, OnUpdateViewWorkspace2)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_COMMAND(ID_VIEW_PROPERTIES, OnViewPropGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateViewPropGrid)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)

	ON_COMMAND(ID_EDIT_SRC_NIC, OnEditSrcNIC)
	ON_COMMAND(ID_EDIT_DEST_NIC, OnEditDestNIC)
	ON_COMMAND(ID_EDIT_RELAY_IP, OnEditRelayIP)

	ON_COMMAND(ID_BTN_LISTNICS, OnBtnListNICs)
	ON_COMMAND(ID_BTN_CAPTURE, OnBtnCapture)
	ON_COMMAND(ID_BTN_STOP, OnBtnStop)
	ON_COMMAND(ID_BTN_CLEAR, OnBtnClear)

	ON_COMMAND(IDC_BTN_DISASM, OnBtnDisasm)

	ON_COMMAND(IDC_BTN_FORWARD, OnBtnForward)

	ON_MESSAGE(ID_GUI_MESSAGE + 0, On_MyMessageBox_Error)
	ON_MESSAGE(ID_GUI_MESSAGE + 1, On_MyMessageBox_Error)
	ON_MESSAGE(ID_GUI_MESSAGE + 2, On_Output_Packets_List)
	ON_MESSAGE(ID_GUI_MESSAGE + 3, On_Output_GetPC_List)
	ON_MESSAGE(ID_GUI_MESSAGE + 4, On_Output_IA32_List)
	ON_MESSAGE(ID_GUI_MESSAGE + 5, On_Output_CFM_List)
	ON_MESSAGE(ID_GUI_MESSAGE + 6, On_Output_DFM_List)
END_MESSAGE_MAP()

HHOOK glhHook;

LRESULT CALLBACK MouseProc(
						   int nCode,      // hook code
						   WPARAM wParam,  // message identifier
						   LPARAM lParam   // mouse coordinates
						   )
{
	if(wParam==WM_LBUTTONDOWN)
    {
		POINT pt = ((MSLLHOOKSTRUCT*)(lParam))-> pt;
		CRect rect;
		
		CMainFrame *pThis = (CMainFrame *) AfxGetApp()->m_pMainWnd;
		
		pThis->GetWindowRect(rect);
		pt.x -= rect.left;
		pt.y -= rect.top;
		
		pt.x -= 8;
		
		CBCGPBaseRibbonElement* selectedElement = pThis->m_wndRibbonBar.HitTest(CPoint(pt.x, pt.y));
		if (selectedElement)
		{
			if (selectedElement->GetParentCategory() == pThis->m_pCategory2)
			{
				CVisualPSDApp *pApp = (CVisualPSDApp *) AfxGetApp();
				pApp->showAboutDlg();
				return 1;
			}
		}
    }
	return CallNextHookEx(glhHook, nCode, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2010_2);

	// TODO: add member initialization code here

	glhHook = SetWindowsHookEx(WH_MOUSE, MouseProc, 0, GetCurrentThreadId());

	doWithTheAPIHookStuff();
	pThis = this;
	m_pDisasmThread = NULL;
	m_disasmer = NULL;
	m_filter = NULL;
	m_initSrcNIC = _T("1");
	m_initDstNIC = _T("");
	m_initRelayIP = _T("192.168.1.233");
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	// TODO: add your status bar panes here:
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE1, _T("北航·网络技术北京市重点实验室"), TRUE), _T("北航·网络技术北京市重点实验室"));
	
	///////////////////////进度条////////////////////////
	m_pProgress = new CBCGPRibbonProgressBar (1, 150);
	m_pProgress->SetInfiniteMode(FALSE);
	m_wndStatusBar.AddExtendedElement(m_pProgress, _T("进度指示器"), TRUE);
	m_pStatusLabel = new CBCGPRibbonStatusBarPane(ID_STATUSBAR_PANE2, _T("Running"), TRUE);
	m_pStatusLabel->SetText(_T("Get Ready"));
	m_wndStatusBar.AddExtendedElement(m_pStatusLabel, _T("当前状态"));
	///////////////////////进度条///////////////////////

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	if (!m_wndWorkSpace.Create (_T("View  1"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!m_wndWorkSpace2.Create (_T("View 2"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar 2\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace2.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);

	if (!m_wndOutput.Create (_T("Output"), this, CRect (0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	m_wndOutput.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

	if (!m_wndPropGrid.Create (_T("Properties"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}

	m_wndPropGrid.SetIcon (imagesWorkspace.ExtractIcon (3), FALSE);
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPropGrid.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar (&m_wndWorkSpace);
	m_wndWorkSpace2.AttachToTabWnd (&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	DockControlBar(&m_wndPropGrid);
	DockControlBar(&m_wndOutput);


	OnAppLook (m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	m_wndRibbonBar.SetScenicLook(FALSE);
	m_wndRibbonBar.EnableMinimizeButton(FALSE);

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:

		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2010_1:
	case ID_VIEW_APPLOOK_2010_2:
	case ID_VIEW_APPLOOK_2010_3:
		// enable Office 2010 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2010_1:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
			break;

		case ID_VIEW_APPLOOK_2010_2:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
			break;

		case ID_VIEW_APPLOOK_2010_3:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Silver);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));

		m_wndRibbonBar.SetScenicLook();
		m_wndRibbonBar.EnableMinimizeButton();

		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WIN7:
		// enable Windows 7 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerScenic));

		m_wndRibbonBar.SetScenicLook();

		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	default:
		CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
		//ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::CreateRibbonBar ()
{
	m_wndRibbonBar.EnableCustomization();

	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize (CSize (16, 16));
	m_PanelImages.Load (IDB_RIBBON_ICONS);

	// Init main button:
	m_MainButton.SetImage (IDB_RIBBON_MAIN);
	m_MainButton.SetToolTipText (_T("File"));
	m_MainButton.SetText (_T("\nf"));

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("File"), IDB_RIBBON_FILESMALL, IDB_RIBBON_FILELARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_NEW, _T("&New"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_OPEN, _T("&Open..."), 1, 1));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 2, 2));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 3, 3));


	pMainPanel->AddRecentFilesList (_T("Recent Documents"), 300, TRUE /* Show Pins */);

	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 9));
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_APP_EXIT, _T("E&xit"), 8));

	// Add "Home" category with "Clipboard" panel:
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("&Home"),
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);
	m_pCategory1 = pCategory;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create "Clipboard" panel:
	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel(_T("Clipboard"), 
		m_PanelImages.ExtractIcon (1));

	CBCGPRibbonButton* pBtnPaste = new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste\nv"), 0, 0);
	pBtnPaste->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pBtnPaste);
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut\nx"), 1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy\nc"), 2));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CLEAR, _T("Erase\nr"), 3));
	pPanelClipboard->SetKeys (_T("zc"));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create "Window" panel:
	CBCGPRibbonPanel* pPanelWindow = pCategory->AddPanel(_T("Window"), 
		m_PanelImages.ExtractIcon (2));

	//pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE, _T("View 1\n1")));
	//pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_WORKSPACE2, _T("View 2\n2")));
	pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_OUTPUT, _T("Output\no")));
	pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_PROPERTIES, _T("Property Grid\ng")));
	pPanelWindow->Add (new CBCGPRibbonCheckBox (ID_VIEW_STATUS_BAR, _T("Status Bar\ns")));
	pPanelWindow->SetKeys (_T("zw"));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create "Network Capture" panel:
	CBCGPRibbonPanel* pPanelNetworkCapture = pCategory->AddPanel(_T("Network Filtering"));
	m_pEditSrcNIC = new CBCGPRibbonEdit(ID_EDIT_SRC_NIC, 60, _T("Source      NIC:"));
	m_pEditSrcNIC->SetTextAlign(ES_CENTER);
	m_pEditSrcNIC->SetEditText(m_initSrcNIC);
	m_pEditDstNIC = new CBCGPRibbonEdit(ID_EDIT_DEST_NIC, 60, _T("Destination NIC:"));
	m_pEditDstNIC->SetTextAlign(ES_CENTER);
	m_pEditDstNIC->SetEditText(m_initDstNIC);
	m_pEditRelayIP = new CBCGPRibbonEdit(ID_EDIT_RELAY_IP, 100, _T("Relay IP:"));
	m_pEditRelayIP->SetTextAlign(ES_CENTER);
	m_pEditRelayIP->SetEditText(m_initRelayIP);

	CBCGPRibbonButton* pBtnListNICs = new CBCGPRibbonButton(ID_BTN_LISTNICS, _T("List NICs\nl"), 0, 3);
	CBCGPRibbonButton* pBtnCapture = new CBCGPRibbonButton(ID_BTN_CAPTURE, _T("Capture\nc"), 0, 5);
	CBCGPRibbonButton* pBtnStop = new CBCGPRibbonButton(ID_BTN_STOP, _T("Stop\ns"), 0, 6);
	CBCGPRibbonButton* pBtnClear = new CBCGPRibbonButton(ID_BTN_CLEAR, _T("Clear\ne"), 0, 4);
	
	pPanelNetworkCapture->Add (m_pEditSrcNIC);
	pPanelNetworkCapture->Add (m_pEditDstNIC);
	pPanelNetworkCapture->Add (m_pEditRelayIP);
	pPanelNetworkCapture->Add (pBtnListNICs);
	pPanelNetworkCapture->Add (pBtnCapture);
	pPanelNetworkCapture->Add (pBtnStop);
	pPanelNetworkCapture->Add (pBtnClear);
	pPanelNetworkCapture->SetKeys (_T("zl"));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create "Analysis" panel:
	CBCGPRibbonPanel* pPanelAnalysis = pCategory->AddPanel(_T("Analysis"));

	CBCGPRibbonButton* pBtnDisassemble = new CBCGPRibbonButton(IDC_BTN_DISASM, _T("Capture && Disassemble\nd"), 0, 3);

	pPanelAnalysis->Add (pBtnDisassemble);
	pPanelAnalysis->SetKeys (_T("zl"));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create "Simulation" panel:
	CBCGPRibbonPanel* pPanelSimulation = pCategory->AddPanel(_T("Simulation"));
	
	CBCGPRibbonButton* pBtnForward = new CBCGPRibbonButton(IDC_BTN_FORWARD, _T("Forward the table\nd"), 0, 3);
	
	pPanelSimulation->Add (pBtnForward);
	pPanelSimulation->SetKeys (_T("zl"));

	// Add some hidden (non-ribbon) elements:
	CBCGPRibbonUndoButton* pUndo = new CBCGPRibbonUndoButton (ID_EDIT_UNDO, _T("Undo"), 4);

	pUndo->AddUndoAction (_T("Undo Item 1"));
	pUndo->AddUndoAction (_T("Undo Item 2"));
	pUndo->AddUndoAction (_T("Undo Item 3"));
	pUndo->AddUndoAction (_T("Undo Item 4"));
	pUndo->AddUndoAction (_T("Undo Item 5"));

	pCategory->AddHidden (pUndo);

	// Add "<TODO>" category with "Clipboard" panel:
	CBCGPRibbonCategory* pTODOCategory = m_wndRibbonBar.AddCategory (
		_T("&About"), 
		0 /* TODO: ID-category small images */, 
		0 /* TODO: ID-category large images */);
	m_pCategory2 = pTODOCategory;

	// Add quick access toolbar commands:
	CBCGPRibbonQATDefaultState qatState;

	qatState.AddCommand (ID_FILE_NEW, FALSE);
	qatState.AddCommand (ID_FILE_OPEN, FALSE);
	qatState.AddCommand (ID_FILE_SAVE);
	qatState.AddCommand (ID_FILE_PRINT_DIRECT);
	qatState.AddCommand (ID_FILE_PRINT_PREVIEW, FALSE);
	qatState.AddCommand (ID_EDIT_UNDO);

	m_wndRibbonBar.SetQuickAccessDefaultState (qatState);

	// Add "Style" button to the right of tabs:
	CBCGPRibbonButton* pStyleButton = new CBCGPRibbonButton (-1, _T("Style\ns"), -1, -1);
	pStyleButton->SetMenu (IDR_THEME_MENU, TRUE /* Right align */);

	m_wndRibbonBar.AddToTabs (pStyleButton);

	// Add "About" button to the right of tabs:
	m_wndRibbonBar.AddToTabs (new CBCGPRibbonButton (ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));

	return TRUE;
}

LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM /*lp*/)
{
	ShowOptions (wp == 0 ? 1 : 0);
	return 1;
}

void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}

void CMainFrame::ShowOptions (int nPage)
{
	// Create custom categories:
	
	// "Popular" items:
	CList<UINT, UINT> lstPopular;
	
	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_EDIT_UNDO);
	
	// Hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);
	
	// All commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);
	
	// Create "Customize QAT" page:
	CBCGPRibbonCustomizeQATPage pageCustomizeQAT(&m_wndRibbonBar);

	pageCustomizeQAT.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeQAT.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeQAT.AddCustomCategory (_T("All Commands"), lstAll);

	// Create Customize Ribbon" page:
	CBCGPRibbonCustomizeRibbonPage pageCustomizeRibbon(&m_wndRibbonBar);

	pageCustomizeRibbon.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeRibbon.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeRibbon.AddCustomCategory (_T("All Commands"), lstAll);

	// Create property sheet:
	CBCGPPropertySheet propSheet (_T("Options"), this, nPage);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.SetLook(CBCGPPropertySheet::PropSheetLook_List, 150 /* List width */);

	propSheet.AddPage (&pageCustomizeRibbon);

	propSheet.AddPage (&pageCustomizeQAT);

	// TODO: add your option pages here:
	// COptionsPage1 pageOptions1;
	// propSheet.AddPage (&pageOptions1);
	//
	// COptionsPage1 pageOptions2;
	// propSheet.AddPage (&pageOptions2);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}


void CMainFrame::OnViewWorkspace() 
{
	ShowControlBar (&m_wndWorkSpace,
					!(m_wndWorkSpace.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWorkSpace.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

void CMainFrame::OnViewWorkspace2() 
{
	ShowControlBar (&m_wndWorkSpace2,
					!(m_wndWorkSpace2.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWorkSpace2.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

void CMainFrame::OnViewOutput() 
{
	ShowControlBar (&m_wndOutput,
					!(m_wndOutput.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutput.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

void CMainFrame::OnViewPropGrid() 
{
	ShowControlBar (&m_wndPropGrid,
					!(m_wndPropGrid.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewPropGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropGrid.IsVisible ());
	pCmdUI->Enable (!GetDockManager ()->IsPrintPreviewValid ());
}

LRESULT CMainFrame::On_MyMessageBox_Error(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strText = pParam->strParam1;
	CString strCaption = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	if (strCaption == _T(""))
	{
		strText = strText + _T(" Error.");
		strCaption = _T("Error");
	}
	
	BCGP_MSGBOXPARAMS params;
	
	params.lpszCaption = strCaption;
	params.lpszText = strText;
	params.bDrawButtonsBanner = TRUE;
	params.bUseNativeControls = FALSE;
	
	params.dwStyle = MB_OK;
	params.bIgnoreStandardButtons = FALSE;
	params.bShowCheckBox = FALSE;
	
	params.dwStyle |= MB_ICONEXCLAMATION;
	
	int result = BCGPMessageBoxIndirect(&params);
	
	//On_ProgressBar_Stop(NULL, NULL);
	
	return 0;
}

LRESULT CMainFrame::On_Output_Packets_List(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strNo = pParam->strParam1;
	CString strContent = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	COutputBar *outputBar = &m_wndOutput;
	outputBar->insert2PacketsList(strNo, strContent);
	
	return 0;
}

LRESULT CMainFrame::On_Output_GetPC_List(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strNo = pParam->strParam1;
	CString strContent = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	COutputBar *outputBar = &m_wndOutput;
	outputBar->insert2GetPCList(strNo, strContent);
	
	return 0;
}

LRESULT CMainFrame::On_Output_IA32_List(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strNo = pParam->strParam1;
	CString strContent = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	COutputBar *outputBar = &m_wndOutput;
	outputBar->insert2IA32List(strNo, strContent);
	
	return 0;
}

LRESULT CMainFrame::On_Output_CFM_List(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strNo = pParam->strParam1;
	CString strContent = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	COutputBar *outputBar = &m_wndOutput;
	outputBar->insert2CFMList(strNo, strContent);
	
	return 0;
}

LRESULT CMainFrame::On_Output_DFM_List(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	CString strNo = pParam->strParam1;
	CString strContent = pParam->strParam2;
	delete pParam;
	pParam = NULL;
	
	COutputBar *outputBar = &m_wndOutput;
	outputBar->insert2DFMList(strNo, strContent);
	
	return 0;
}

CString CMainFrame::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

int CMainFrame::stoi(CString s)
{
	return atoi(s);
}

DWORD WINAPI FilterThread(LPVOID lpParameter)
{
	int iSrcNIC = -1;
	int iDestNIC = -1;
	if (pThis->m_filter)
	{
		delete pThis->m_filter;
		pThis->m_filter = NULL;
	}
	pThis->m_filter = new PSFilter();

	if (pThis->m_pEditSrcNIC->GetEditText() == "")
	{
		MyMessageBox_Error("No source NIC");
	}
	else if (pThis->m_pEditDstNIC->GetEditText() == "")
	{
		iSrcNIC = pThis->stoi(pThis->m_pEditSrcNIC->GetEditText());
		pThis->m_filter->captureNIC(iSrcNIC);
	}
	else
	{
		iSrcNIC = pThis->stoi(pThis->m_pEditSrcNIC->GetEditText());
		iDestNIC = pThis->stoi(pThis->m_pEditDstNIC->GetEditText());
		pThis->m_filter->captureNIC(iSrcNIC, iDestNIC);
	}
	
	return 0;
}

void CMainFrame::OnBtnListNICs()
{
	if (m_filter)
	{
		delete m_filter;
		m_filter = NULL;
	}
	m_filter = new PSFilter();
	m_filter->listNICs();
}

void CMainFrame::OnBtnCapture()
{
	HANDLE hFilterThread = CreateThread(NULL, 0, FilterThread, this, 0, NULL);
	if (hFilterThread == NULL)
	{
		MyMessageBox_Error(_T("OnBtnCapture"));
	}
	else
	{
		CloseHandle(hFilterThread);
	}
}

void CMainFrame::OnBtnStop()
{
	m_filter->stop();
}

void CMainFrame::OnBtnClear()
{
	m_wndOutput.clearPacketsList();
	m_wndOutput.clearGetPCList();
	m_wndOutput.clearIA32List();
	m_wndOutput.clearCFMList();
	m_wndOutput.clearDFMList();
	CVisualPSDView *pView = (CVisualPSDView*) GetActiveView();
	pView->clearDumpEditBox2();
	pView->clearTextEditBox2();
}

void CMainFrame::OnBtnDisasm()
{
	if (m_pDisasmThread == NULL)
	{
		m_pDisasmThread = (CPSDisasmThread*) AfxBeginThread(RUNTIME_CLASS(CPSDisasmThread));
	}
	OnBtnCapture();
}

void CMainFrame::OnBtnForward()
{
	CString strRelayIP = m_pEditRelayIP->GetEditText();
	if (!PSForwarder::checkIP(strRelayIP))
	{
		MyMessageBox_Error(_T("OnBtnForward"));
		return;
	}

	if (m_filter)
	{
		delete m_filter;
		m_filter = NULL;
	}
	m_filter = new PSFilter();
	m_filter->listNICs(FALSE);
	m_filter->setReserveNICs(TRUE);

	if (m_forwarder)
	{
		delete m_forwarder;
		m_forwarder = NULL;
	}
	m_forwarder = new PSForwarder(strRelayIP, m_filter->m_nNICs);
	m_forwarder->readListFromFile();
}

void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	CVisualPSDView *pView = (CVisualPSDView*) GetActiveView();
}
