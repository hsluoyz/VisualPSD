// VisualPSDView.h : interface of the CVisualPSDView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALPSDVIEW_H__57BC8B4A_520C_4453_9C0C_AD5B655983AD__INCLUDED_)
#define AFX_VISUALPSDVIEW_H__57BC8B4A_520C_4453_9C0C_AD5B655983AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
class CVisualPSDDoc;
#include "MyRichEditCtrl.h"

#define CFormView CBCGPFormView

class CVisualPSDView : public CFormView
{
protected: // create from serialization only
	CVisualPSDView();
	DECLARE_DYNCREATE(CVisualPSDView)

public:
	//{{AFX_DATA(CVisualPSDView)
	enum { IDD = IDD_VISUALPSD_FORM };
	CMyRichEditCtrl	m_editDump;
	CMyRichEditCtrl	m_editText;
	CMyRichEditCtrl	m_editDump2;
	CMyRichEditCtrl	m_editText2;
	//}}AFX_DATA

// Attributes
public:
	CVisualPSDDoc* GetDocument();

// Operations
public:
	CString itos(int i);
	int stoi(CString s);
	void ResizeEdits();
	void SynchronizeEdits(CMyRichEditCtrl *pEdit);
	void clearDumpEditBox2();
	void clearTextEditBox2();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPSDView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualPSDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualPSDView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);

	afx_msg LRESULT On_Output_Dump_EditBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_Text_EditBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_Dump_EditBox2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On_Output_Text_EditBox2(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VisualPSDView.cpp
inline CVisualPSDDoc* CVisualPSDView::GetDocument()
   { return (CVisualPSDDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPSDVIEW_H__57BC8B4A_520C_4453_9C0C_AD5B655983AD__INCLUDED_)
