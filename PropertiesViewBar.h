// PropertiesViewBar.h : interface of the CPropertiesBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIESVIEWBAR_H__3D4EE607_AC8B_468F_8708_9A31625BFAD6__INCLUDED_)
#define AFX_PROPERTIESVIEWBAR_H__3D4EE607_AC8B_468F_8708_9A31625BFAD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPropertiesBar : public CBCGPDockingControlBar  
{
// Construction
public:
	CPropertiesBar();

	void AdjustLayout ();

// Attributes
public:
	void SetVSDotNetLook (BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook (bSet);
		m_wndPropList.SetGroupNameFullWidth (bSet);
	}

protected:
	CBCGPPropList		m_wndPropList;

	CBCGPColor			m_BorderColor;
	CBCGPBrush			m_FillBrush;
	CBCGPBrush			m_TextBrush;

// Attributes
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertiesBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandClicked(WPARAM, LPARAM);
	afx_msg LRESULT OnMenuItemSelected(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	void InitPropList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESVIEWBAR_H__3D4EE607_AC8B_468F_8708_9A31625BFAD6__INCLUDED_)
