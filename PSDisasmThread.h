#if !defined(AFX_PSDISASMTHREAD_H__FEBE26D1_5E96_4F8D_B143_EE2925C1CB9C__INCLUDED_)
#define AFX_PSDISASMTHREAD_H__FEBE26D1_5E96_4F8D_B143_EE2925C1CB9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSDisasmThread.h : header file
//

class PSDisasmer;
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPSDisasmThread thread

class CPSDisasmThread : public CWinThread
{
	DECLARE_DYNCREATE(CPSDisasmThread)
protected:
	CPSDisasmThread();           // protected constructor used by dynamic creation

// Attributes
public:
	vector<PSShellcode*> m_nShellcodes;
	PSDisasmer *m_disasmer;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSDisasmThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPSDisasmThread();

	// Generated message map functions
	//{{AFX_MSG(CPSDisasmThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT On_Output_Shellcode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSDISASMTHREAD_H__FEBE26D1_5E96_4F8D_B143_EE2925C1CB9C__INCLUDED_)
