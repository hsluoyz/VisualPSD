#if !defined(AFX_VISUALPSDABOUTDLG_H__EA595137_F781_4AAA_BE2D_F89DFE3BB74E__INCLUDED_)
#define AFX_VISUALPSDABOUTDLG_H__EA595137_F781_4AAA_BE2D_F89DFE3BB74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPSDAboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDAboutDlg dialog

class CVisualPSDAboutDlg : public CDialog
{
// Construction
public:
	CVisualPSDAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisualPSDAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CEdit	m_editAbout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPSDAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPSDAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCompanyUrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPSDABOUTDLG_H__EA595137_F781_4AAA_BE2D_F89DFE3BB74E__INCLUDED_)
