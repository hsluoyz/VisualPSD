// VisualPSDDoc.cpp : implementation of the CVisualPSDDoc class
//

#include "stdafx.h"
#include "VisualPSD.h"

#include "VisualPSDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDDoc

IMPLEMENT_DYNCREATE(CVisualPSDDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisualPSDDoc, CDocument)
	//{{AFX_MSG_MAP(CVisualPSDDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDDoc construction/destruction

CVisualPSDDoc::CVisualPSDDoc()
{
	// TODO: add one-time construction code here

}

CVisualPSDDoc::~CVisualPSDDoc()
{
}

BOOL CVisualPSDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle(_T("基于双模式虚拟机的多态Shellcode检测系统"));
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisualPSDDoc serialization

void CVisualPSDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDDoc diagnostics

#ifdef _DEBUG
void CVisualPSDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisualPSDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDDoc commands
