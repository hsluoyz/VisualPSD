#if !defined(AFX_PSIA32THREAD_H__D7720930_1616_429F_BD86_DAC13477C97A__INCLUDED_)
#define AFX_PSIA32THREAD_H__D7720930_1616_429F_BD86_DAC13477C97A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSIA32Thread.h : header file
//

class PSIA32Recognizer;
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPSIA32Thread thread

class CPSIA32Thread : public CWinThread
{
	DECLARE_DYNCREATE(CPSIA32Thread)
protected:
	CPSIA32Thread();           // protected constructor used by dynamic creation

// Attributes
public:
	vector<PSShellcode*> m_nShellcodes;
	PSIA32Recognizer *m_recognizer;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSIA32Thread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPSIA32Thread();

	// Generated message map functions
	//{{AFX_MSG(CPSIA32Thread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT On_Output_Shellcode(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSIA32THREAD_H__D7720930_1616_429F_BD86_DAC13477C97A__INCLUDED_)
