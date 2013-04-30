// PSCFMThread.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "PSCFMThread.h"
#include "PSCFMAnalyzer.h"

class PSShellcode;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GUI_MESSAGE 0x1060

/////////////////////////////////////////////////////////////////////////////
// CPSCFMThread

IMPLEMENT_DYNCREATE(CPSCFMThread, CWinThread)

CPSCFMThread::CPSCFMThread()
{
	m_analyzer = new PSCFMAnalyzer();
}

CPSCFMThread::~CPSCFMThread()
{
	if (m_analyzer != NULL)
	{
		delete m_analyzer;
		m_analyzer = NULL;
	}
}

BOOL CPSCFMThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPSCFMThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPSCFMThread, CWinThread)
	//{{AFX_MSG_MAP(CPSCFMThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_GUI_MESSAGE + 22, On_Output_Shellcode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSCFMThread message handlers

LRESULT CPSCFMThread::On_Output_Shellcode(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	PSShellcode *shellcode = (PSShellcode*) pParam->pObject1;
	delete pParam;
	pParam = NULL;
	
	if (shellcode == NULL || m_analyzer == NULL)
	{
		MyMessageBox_Error("On_Output_Shellcode");
		return 0;
	}
	
	m_nShellcodes.push_back(shellcode);
	//m_analyzer->disasmShellcode(shellcode);
	
	return 0;
}