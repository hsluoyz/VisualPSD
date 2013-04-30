// OutputBar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here

}

COutputBar::~COutputBar()
{
}

void COutputBar::initPacketsList()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listPackets.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listPackets.m_hWnd, GWL_STYLE, lStyle); //设置style
	
	m_listPackets.SetExtendedStyle(m_listPackets.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	m_listPackets.InsertColumn(0, _T("Packet No."));
	m_listPackets.InsertColumn(1, _T("Description"));
	m_listPackets.SetColumnWidth(0, 70);
}

void COutputBar::insert2PacketsList(CString strNo, CString strContent)
{
	int iLimit = m_listPackets.GetScrollLimit(SB_VERT);
	int iPos = m_listPackets.GetScrollPos(SB_VERT);

	m_listPackets.InsertItem(m_listPackets.GetItemCount(), strNo);
	m_listPackets.SetItemText(m_listPackets.GetItemCount() - 1, 1, strContent);

	if (iLimit == iPos)
	{
		m_listPackets.EnsureVisible(m_listPackets.GetItemCount() - 1, FALSE);
	}
}

void COutputBar::clearPacketsList()
{
	m_listPackets.DeleteAllItems();
}

void COutputBar::initGetPCList()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listGetPC.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listGetPC.m_hWnd, GWL_STYLE, lStyle); //设置style
	
	m_listGetPC.SetExtendedStyle(m_listGetPC.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	m_listGetPC.InsertColumn(0, _T("Shellcode No."));
	m_listGetPC.InsertColumn(1, _T("Description"));
	m_listGetPC.SetColumnWidth(0, 90);
}

void COutputBar::insert2GetPCList(CString strNo, CString strContent)
{
	int iLimit = m_listGetPC.GetScrollLimit(SB_VERT);
	int iPos = m_listGetPC.GetScrollPos(SB_VERT);

	m_listGetPC.InsertItem(m_listGetPC.GetItemCount(), strNo);
	m_listGetPC.SetItemText(m_listGetPC.GetItemCount() - 1, 1, strContent);
	
	if (iLimit == iPos)
	{
		m_listGetPC.EnsureVisible(m_listGetPC.GetItemCount() - 1, FALSE);
	}
}

void COutputBar::clearGetPCList()
{
	m_listGetPC.DeleteAllItems();
}

void COutputBar::initIA32List()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listIA32.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listIA32.m_hWnd, GWL_STYLE, lStyle); //设置style
	
	m_listIA32.SetExtendedStyle(m_listIA32.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	m_listIA32.InsertColumn(0, _T("Shellcode No."));
	m_listIA32.InsertColumn(1, _T("Description"));
	m_listIA32.SetColumnWidth(0, 90);
}

void COutputBar::insert2IA32List(CString strNo, CString strContent)
{
	int iLimit = m_listIA32.GetScrollLimit(SB_VERT);
	int iPos = m_listIA32.GetScrollPos(SB_VERT);
	
	m_listIA32.InsertItem(m_listIA32.GetItemCount(), strNo);
	m_listIA32.SetItemText(m_listIA32.GetItemCount() - 1, 1, strContent);
	
	if (iLimit == iPos)
	{
		m_listIA32.EnsureVisible(m_listIA32.GetItemCount() - 1, FALSE);
	}
}

void COutputBar::clearIA32List()
{
	m_listIA32.DeleteAllItems();
}

void COutputBar::initCFMList()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listCFM.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listCFM.m_hWnd, GWL_STYLE, lStyle); //设置style
	
	m_listCFM.SetExtendedStyle(m_listCFM.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	m_listCFM.InsertColumn(0, _T("Shellcode No."));
	m_listCFM.InsertColumn(1, _T("Description"));
	m_listCFM.SetColumnWidth(0, 90);
}

void COutputBar::insert2CFMList(CString strNo, CString strContent)
{
	int iLimit = m_listCFM.GetScrollLimit(SB_VERT);
	int iPos = m_listCFM.GetScrollPos(SB_VERT);
	
	m_listCFM.InsertItem(m_listCFM.GetItemCount(), strNo);
	m_listCFM.SetItemText(m_listCFM.GetItemCount() - 1, 1, strContent);
	
	if (iLimit == iPos)
	{
		m_listCFM.EnsureVisible(m_listCFM.GetItemCount() - 1, FALSE);
	}
}

void COutputBar::clearCFMList()
{
	m_listCFM.DeleteAllItems();
}

void COutputBar::initDFMList()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listDFM.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listDFM.m_hWnd, GWL_STYLE, lStyle); //设置style
	
	m_listDFM.SetExtendedStyle(m_listDFM.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	m_listDFM.InsertColumn(0, _T("Shellcode No."));
	m_listDFM.InsertColumn(1, _T("Description"));
	m_listDFM.SetColumnWidth(0, 90);
}

void COutputBar::insert2DFMList(CString strNo, CString strContent)
{
	int iLimit = m_listDFM.GetScrollLimit(SB_VERT);
	int iPos = m_listDFM.GetScrollPos(SB_VERT);
	
	m_listDFM.InsertItem(m_listDFM.GetItemCount(), strNo);
	m_listDFM.SetItemText(m_listDFM.GetItemCount() - 1, 1, strContent);
	
	if (iLimit == iPos)
	{
		m_listDFM.EnsureVisible(m_listDFM.GetItemCount() - 1, FALSE);
	}
}

void COutputBar::clearDFMList()
{
	m_listDFM.DeleteAllItems();
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create list windows.
	// TODO: create your own window here:
	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	m_listPackets.m_bVisualManagerStyle = TRUE;
	m_listGetPC.m_bVisualManagerStyle = TRUE;
	m_listIA32.m_bVisualManagerStyle = TRUE;
	m_listCFM.m_bVisualManagerStyle = TRUE;
	m_listDFM.m_bVisualManagerStyle = TRUE;
	
	if (!m_listPackets.Create (dwViewStyle, rectDummy, &m_wndTabs, 2) ||
		!m_listGetPC.Create (dwViewStyle, rectDummy, &m_wndTabs, 3) ||
		!m_listIA32.Create (dwViewStyle, rectDummy, &m_wndTabs, 4) ||
		!m_listCFM.Create (dwViewStyle, rectDummy, &m_wndTabs, 5) ||
		!m_listDFM.Create (dwViewStyle, rectDummy, &m_wndTabs, 6))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

	// Attach list windows to tab:
	m_wndTabs.AddTab (&m_listPackets, _T("Packets"), -1);
	m_wndTabs.AddTab (&m_listGetPC, _T("GetPC Location"), -1);
	m_wndTabs.AddTab (&m_listIA32, _T("IA-32 Instruction Recognition"), -1);
	m_wndTabs.AddTab (&m_listCFM, _T("Control-Flow Mode"), -1);
	m_wndTabs.AddTab (&m_listDFM, _T("Data-Flow Mode"), -1);

	initPacketsList();
	initGetPCList();
	initIA32List();
	initCFMList();
	initDFMList();

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listPackets.SetColumnWidth(1, cx - 70 - 6);
	m_listGetPC.SetColumnWidth(1, cx - 90 - 6);
	m_listIA32.SetColumnWidth(1, cx - 90 - 6);
	m_listCFM.SetColumnWidth(1, cx - 90 - 6);
	m_listDFM.SetColumnWidth(1, cx - 90 - 6);
}

CString COutputBar::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

int COutputBar::stoi(CString s)
{
	return atoi(s);
}