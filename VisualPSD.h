// VisualPSD.h : main header file for the VISUALPSD application
//

#if !defined(AFX_VISUALPSD_H__41EF5EE0_5764_4627_8951_E3354FF11184__INCLUDED_)
#define AFX_VISUALPSD_H__41EF5EE0_5764_4627_8951_E3354FF11184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDApp:
// See VisualPSD.cpp for the implementation of this class
//

class CVisualPSDApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CVisualPSDApp();
	void showAboutDlg();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPSDApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVisualPSDApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CVisualPSDApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPSD_H__41EF5EE0_5764_4627_8951_E3354FF11184__INCLUDED_)
