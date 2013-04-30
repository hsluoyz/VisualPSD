#if !defined(AFX_PSCFMTHREAD_H__DDCEED92_8D0C_4E00_8954_3E2797D65382__INCLUDED_)
#define AFX_PSCFMTHREAD_H__DDCEED92_8D0C_4E00_8954_3E2797D65382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSCFMThread.h : header file
//

class PSCFMAnalyzer;
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPSCFMThread thread

class CPSCFMThread : public CWinThread
{
	DECLARE_DYNCREATE(CPSCFMThread)
protected:
	CPSCFMThread();           // protected constructor used by dynamic creation

// Attributes
public:
	vector<PSShellcode*> m_nShellcodes;
	PSCFMAnalyzer *m_analyzer;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSCFMThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPSCFMThread();

	// Generated message map functions
	//{{AFX_MSG(CPSCFMThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT On_Output_Shellcode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSCFMTHREAD_H__DDCEED92_8D0C_4E00_8954_3E2797D65382__INCLUDED_)
