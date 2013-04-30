// PSDisasmThread.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "PSDisasmThread.h"
#include "PSDisasmer.h"

class PSShellcode;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GUI_MESSAGE 0x1060

/////////////////////////////////////////////////////////////////////////////
// CPSDisasmThread

IMPLEMENT_DYNCREATE(CPSDisasmThread, CWinThread)

CPSDisasmThread::CPSDisasmThread()
{
	m_disasmer = new PSDisasmer();
}

CPSDisasmThread::~CPSDisasmThread()
{
	if (m_disasmer != NULL)
	{
		delete m_disasmer;
		m_disasmer = NULL;
	}
}

BOOL CPSDisasmThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPSDisasmThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPSDisasmThread, CWinThread)
	//{{AFX_MSG_MAP(CPSDisasmThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_GUI_MESSAGE + 20, On_Output_Shellcode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSDisasmThread message handlers

LRESULT CPSDisasmThread::On_Output_Shellcode(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	PSShellcode *shellcode = (PSShellcode*) pParam->pObject1;
	delete pParam;
	pParam = NULL;

	if (shellcode == NULL || m_disasmer == NULL)
	{
		MyMessageBox_Error("On_Output_Shellcode");
		return 0;
	}

	m_nShellcodes.push_back(shellcode);
	m_disasmer->disasmShellcode(shellcode);

	return 0;
}
