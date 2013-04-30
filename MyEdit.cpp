// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "MainFrm.h"
#include "VisualPSDView.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) 
{
	// �༭���ݼ����� 
    if(WM_KEYDOWN == pMsg->message)  
    { 
        if(::GetFocus() == m_hWnd && (GetKeyState( VK_CONTROL) & 0xFF00 ) == 0xFF00)  
        { 
            // ȫѡ 
            if( pMsg->wParam == 'A' || pMsg->wParam == 'a') 
            { 
                this->SetSel(0, -1); 
                return true; 
            } 
			
            // ���� 
            if( pMsg->wParam == 'C' || pMsg->wParam == 'c') 
            { 
                this->Copy(); 
                return true; 
            } 
			
            // ���� 
            if( pMsg->wParam == 'X' || pMsg->wParam == 'x') 
            { 
                this->Cut(); 
                return true; 
            } 
			
            // ճ�� 
            if( pMsg->wParam == 'V' || pMsg->wParam == 'v') 
            { 
                this->Paste(); 
                return true; 
            } 
			
            // ճ�� 
            if( pMsg->wParam == 'Z' || pMsg->wParam == 'z') 
            { 
                this->Undo(); 
                return true; 
            } 
			
        } 
    } 	
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	/*
	CMainFrame *pMainWnd = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CVisualPSDView *pView = (CVisualPSDView*) pMainWnd->GetActiveView();
	pView->SynchronizeEdits(this);
	*/

	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);
}
