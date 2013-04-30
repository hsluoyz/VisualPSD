// OutputBar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBAR_H__7554142E_1F08_40C8_9CF2_9811379A522B__INCLUDED_)
#define AFX_OUTPUTBAR_H__7554142E_1F08_40C8_9CF2_9811379A522B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();

// Attributes
protected:
	CBCGPTabWnd	m_wndTabs;

	CBCGPListCtrl	m_listPackets;
	CBCGPListCtrl	m_listGetPC;
	CBCGPListCtrl	m_listIA32;
	CBCGPListCtrl	m_listCFM;
	CBCGPListCtrl	m_listDFM;

// Operations
public:
	void initPacketsList();
	void insert2PacketsList(CString strNo, CString strContent);
	void clearPacketsList();
	void initGetPCList();
	void insert2GetPCList(CString strNo, CString strContent);
	void clearGetPCList();
	void initIA32List();
	void insert2IA32List(CString strNo, CString strContent);
	void clearIA32List();
	void initCFMList();
	void insert2CFMList(CString strNo, CString strContent);
	void clearCFMList();
	void initDFMList();
	void insert2DFMList(CString strNo, CString strContent);
	void clearDFMList();

	CString itos(int i);
	int stoi(CString s);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBAR_H__7554142E_1F08_40C8_9CF2_9811379A522B__INCLUDED_)
