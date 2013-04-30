// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F35EE8F9_4836_402C_8334_E9FCE2F6B8E4__INCLUDED_)
#define AFX_MAINFRM_H__F35EE8F9_4836_402C_8334_E9FCE2F6B8E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WorkspaceBar.h"
#include "WorkspaceBar2.h"
#include "OutputBar.h"
#include "PropertiesViewBar.h"

#define CFrameWnd CBCGPFrameWnd

class CPSDisasmThread;
class PSDisasmer;
class PSFilter;
class PSForwarder;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CBCGPRibbonEdit* m_pEditSrcNIC;
	CBCGPRibbonEdit* m_pEditDstNIC;
	CBCGPRibbonEdit* m_pEditRelayIP;
	CString m_initSrcNIC;
	CString m_initDstNIC;
	CString m_initRelayIP;

	CBCGPRibbonProgressBar* m_pProgress;
	int m_iProgress;
	BOOL m_bProgressing;
	CBCGPRibbonStatusBarPane* m_pStatusLabel;

	CPSDisasmThread *m_pDisasmThread;
	PSDisasmer *m_disasmer;
	PSFilter *m_filter;
	PSForwarder *m_forwarder;

public:  // control bar embedded members
	CBCGPRibbonBar			m_wndRibbonBar;
	CBCGPRibbonCategory *m_pCategory1;
	CBCGPRibbonCategory *m_pCategory2;
	CBCGPRibbonMainButton	m_MainButton;
	CBCGPToolBarImages		m_PanelImages;
	CBCGPRibbonStatusBar m_wndStatusBar;
	CWorkspaceBar		m_wndWorkSpace;
	CWorkspaceBar2		m_wndWorkSpace2;
	COutputBar		m_wndOutput;
	CPropertiesBar		m_wndPropGrid;

public:
	CString itos(int i);
	int stoi(CString s);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void OnToolsOptions();
	afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnViewWorkspace2();
	afx_msg void OnUpdateViewWorkspace2(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnViewPropGrid();
	afx_msg void OnUpdateViewPropGrid(CCmdUI* pCmdUI);

	afx_msg void OnEditSrcNIC(){};
	afx_msg void OnEditDestNIC(){};
	afx_msg void OnEditRelayIP(){};

	afx_msg void OnBtnListNICs();
	afx_msg void OnBtnCapture();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnDisasm();
	afx_msg void OnBtnForward();

	afx_msg LRESULT On_MyMessageBox_Error(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_Packets_List(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_GetPC_List(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_IA32_List(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_CFM_List(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_DFM_List(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	void ShowOptions (int nPage);

	UINT	m_nAppLook;
};

DWORD WINAPI FilterThread(LPVOID lpParameter);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F35EE8F9_4836_402C_8334_E9FCE2F6B8E4__INCLUDED_)
