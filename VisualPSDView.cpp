// VisualPSDView.cpp : implementation of the CVisualPSDView class
//

#include "stdafx.h"
#include "VisualPSD.h"

#include "VisualPSDDoc.h"
#include "VisualPSDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GUI_MESSAGE 0x1060

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDView

IMPLEMENT_DYNCREATE(CVisualPSDView, CFormView)

BEGIN_MESSAGE_MAP(CVisualPSDView, CFormView)
	//{{AFX_MSG_MAP(CVisualPSDView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()

	ON_MESSAGE(ID_GUI_MESSAGE + 10, On_Output_Dump_EditBox)
	ON_MESSAGE(ID_GUI_MESSAGE + 11, On_Output_Text_EditBox)
	ON_MESSAGE(ID_GUI_MESSAGE + 12, On_Output_Dump_EditBox2)
	ON_MESSAGE(ID_GUI_MESSAGE + 13, On_Output_Text_EditBox2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDView construction/destruction

CVisualPSDView::CVisualPSDView()
	: CFormView(CVisualPSDView::IDD)
{
	//{{AFX_DATA_INIT(CVisualPSDView)
	//}}AFX_DATA_INIT

	EnableVisualManagerStyle();

	// TODO: add construction code here

}

CVisualPSDView::~CVisualPSDView()
{
}

void CVisualPSDView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPSDView)
	DDX_Control(pDX, IDC_RICHEDIT_TEXT, m_editText2);
	DDX_Control(pDX, IDC_EDIT_DUMP, m_editDump);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
	DDX_Control(pDX, IDC_RICHEDIT_DUMP, m_editDump2);
	//}}AFX_DATA_MAP
}

BOOL CVisualPSDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_VSCROLL;
	cs.style &= ~WS_HSCROLL;
	return CFormView::PreCreateWindow(cs);
}

void CVisualPSDView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	EnableScrollBarCtrl(SB_BOTH, FALSE);
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	ResizeEdits();

	//m_editDump.SetLimitText(-1);
	//m_editText.SetLimitText(-1);
	m_editDump2.LimitText(2147483647);
	m_editText2.LimitText(2147483647);
}

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDView diagnostics

#ifdef _DEBUG
void CVisualPSDView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVisualPSDView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVisualPSDDoc* CVisualPSDView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisualPSDDoc)));
	return (CVisualPSDDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDView message handlers

CString CVisualPSDView::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

int CVisualPSDView::stoi(CString s)
{
	return atoi(s);
}

void CVisualPSDView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CVisualPSDView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (m_editDump && m_editText)
	{
		ResizeEdits();
	}
}

void CVisualPSDView::ResizeEdits()
{
	CRect rect;
	this->GetClientRect(rect);

	CRect rect2 = rect;
	rect2.DeflateRect(0, 0, rect.Width() / 2, rect.Height() / 4);
	CRect rect3 = rect2;
	rect3.OffsetRect(rect.Width() / 2, 0);

	rect2.DeflateRect(10, 10, 5, 10);
	rect3.DeflateRect(5, 10, 10, 10);

	/*
	CRect rect4 = rect;
	rect4.DeflateRect(0, rect.Height() * 3 / 4, rect.Width() / 2, 0);
	rect4.DeflateRect(10, 0, 5, 10);

	CRect rect5 = rect;
	rect5.DeflateRect(rect.Width() / 2, rect.Height() * 3 / 4, 0, 0);
	rect5.DeflateRect(5, 0, 10, 10);
	*/

	m_editDump2.MoveWindow(rect2);
	m_editText2.MoveWindow(rect3);

	CSize size;
	size.cx = rect.right;
	size.cy = rect.bottom;
	SetScrollSizes(MM_TEXT, size);
}

LRESULT CVisualPSDView::On_Output_Dump_EditBox(WPARAM wParam, LPARAM lParam)
{
	int iLimit = m_editDump.GetScrollLimit(SB_VERT);
	int iPos = m_editDump.GetScrollPos(SB_VERT);

	PMParam *pParam = (PMParam *) wParam;
	CString strContent = pParam->strParam1 + "\r\n";
	int iIndex = m_editDump.GetWindowTextLength();
	m_editDump.SetSel(iIndex, iIndex);
	m_editDump.ReplaceSel(strContent);
	//CString strTemp;
	//m_editDump.GetWindowText(strTemp);
	//strTemp += pParam->strParam1;
	//strTemp += "\r\n";
	//m_editDump.SetWindowText(strTemp);

	if (iLimit == iPos)
	{
		//iLimit = m_editDump.GetScrollLimit(SB_VERT);
		//m_editDump.LineScroll(m_editDump.GetLineCount());
	}
	else
	{
		//m_editDump.LineScroll(iPos);
	}

	delete pParam;
	pParam = NULL;
	return 0;
}

LRESULT CVisualPSDView::On_Output_Text_EditBox(WPARAM wParam, LPARAM lParam)
{
	int iLimit = m_editText.GetScrollLimit(SB_VERT);
	int iPos = m_editText.GetScrollPos(SB_VERT);

	PMParam *pParam = (PMParam *) wParam;
	CString strContent = pParam->strParam1 + "\r\n";
	int iIndex = m_editText.GetWindowTextLength();
	m_editText.SetSel(iIndex, iIndex);
	m_editText.ReplaceSel(strContent);

	int iPos2 = m_editText.GetScrollPos(SB_VERT);
	m_editText.LineScroll(iPos - iPos2);
	//CString strTemp;
	//m_editText.GetWindowText(strTemp);
	//strTemp += pParam->strParam1;
	//strTemp += "\r\n";
	//m_editText.SetWindowText(strTemp);

	if (iLimit == iPos)
	{
		//iLimit = m_editText.GetScrollLimit(SB_VERT);
		//m_editText.LineScroll(m_editText.GetLineCount());
	}
	else
	{
		//m_editText.LineScroll(iPos);
	}
	
	delete pParam;
	pParam = NULL;
	return 0;
}

int iDumpEditBox2Flag;
LRESULT CVisualPSDView::On_Output_Dump_EditBox2(WPARAM wParam, LPARAM lParam)
{
	int iLimit = m_editDump2.GetScrollLimit(SB_VERT);
	int iPos = m_editDump2.GetScrollPos(SB_VERT);
	
	
	PMParam *pParam = (PMParam *) wParam;
	CMyRichEditCtrl *pEdit = pParam->pObject1;
	if (pEdit == NULL)
	{
		
		return 0;
	}
	CString strContent = pParam->strParam1;
	
	if (m_editDump2.GetWindowTextLength() == 0)
	{
		iDumpEditBox2Flag = 1;
	}
	else
	{
		strContent = "\r\n" + strContent;
	}
	
	int iLineOld, iLineNew;
	iLineOld = m_editDump2.GetFirstVisibleLine();
	
	int iTotalTextLength = m_editDump2.GetWindowTextLength();
	m_editDump2.SetSel(iTotalTextLength, iTotalTextLength);
	m_editDump2.ReplaceSel(strContent);
	m_editDump2.HideSelection(TRUE, FALSE);
	
	iLineNew = m_editDump2.GetFirstVisibleLine();
	
	if (iLimit - iPos <= 30 || iDumpEditBox2Flag)
	{
		if (iLimit - iPos <= 30)
		{
			iDumpEditBox2Flag = 0;
		}
		int iLimitNew = m_editDump2.GetScrollLimit(SB_VERT);
		int iPosNew = m_editDump2.GetScrollPos(SB_VERT);
		m_editDump2.LineScroll(iLimitNew - iPosNew);
	}
	else
	{
		m_editDump2.LineScroll(iLineOld - iLineNew);
	}
	
	delete pParam;
	pParam = NULL;
	return 0;
}

int iTextEditBox2Flag;
LRESULT CVisualPSDView::On_Output_Text_EditBox2(WPARAM wParam, LPARAM lParam)
{
	int iLimit = m_editText2.GetScrollLimit(SB_VERT);
	int iPos = m_editText2.GetScrollPos(SB_VERT);
	
	
	PMParam *pParam = (PMParam *) wParam;
	CString strContent = pParam->strParam1;
	
	if (m_editText2.GetWindowTextLength() == 0)
	{
		iTextEditBox2Flag = 1;
	}
	else
	{
		strContent = "\r\n" + strContent;
	}
	
	int iLineOld, iLineNew;
	iLineOld = m_editText2.GetFirstVisibleLine();
	
	int iTotalTextLength = m_editText2.GetWindowTextLength();
	m_editText2.SetSel(iTotalTextLength, iTotalTextLength);
	m_editText2.ReplaceSel(strContent);
	m_editText2.HideSelection(TRUE, FALSE);
	
	iLineNew = m_editText2.GetFirstVisibleLine();
	
	if (iLimit - iPos <= 30 || iTextEditBox2Flag)
	{
		if (iLimit - iPos <= 30)
		{
			iTextEditBox2Flag = 0;
		}
		int iLimitNew = m_editText2.GetScrollLimit(SB_VERT);
		int iPosNew = m_editText2.GetScrollPos(SB_VERT);
		m_editText2.LineScroll(iLimitNew - iPosNew);
	}
	else
	{
		m_editText2.LineScroll(iLineOld - iLineNew);
	}
	
	delete pParam;
	pParam = NULL;
	return 0;
}

void CVisualPSDView::clearDumpEditBox2()
{
	m_editDump2.SetWindowText("");
}

void CVisualPSDView::clearTextEditBox2()
{
	m_editText2.SetWindowText("");
}

void CVisualPSDView::SynchronizeEdits(CMyRichEditCtrl *pEdit)
{
	CMyRichEditCtrl *pEditTarget;
	if (pEdit == &m_editText2)
	{
		pEditTarget = &m_editDump2;
	}
	else if (pEdit == &m_editDump2)
	{
		pEditTarget = &m_editText2;
	}
	int iPos = pEdit->GetFirstVisibleLine();
	int iPosTarget = pEditTarget->GetFirstVisibleLine();

	if (iPos != iPosTarget)
	{
		pEditTarget->LineScroll(iPos - iPosTarget);
	}
}
