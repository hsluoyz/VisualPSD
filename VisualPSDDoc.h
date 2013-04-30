// VisualPSDDoc.h : interface of the CVisualPSDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALPSDDOC_H__98851D8B_0FFE_4970_ADF0_F941CC7395C4__INCLUDED_)
#define AFX_VISUALPSDDOC_H__98851D8B_0FFE_4970_ADF0_F941CC7395C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisualPSDDoc : public CDocument
{
protected: // create from serialization only
	CVisualPSDDoc();
	DECLARE_DYNCREATE(CVisualPSDDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPSDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualPSDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualPSDDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPSDDOC_H__98851D8B_0FFE_4970_ADF0_F941CC7395C4__INCLUDED_)
