// PSIA32Thread.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "PSIA32Thread.h"
#include "PSIA32Recognizer.h"

class PSShellcode;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_GUI_MESSAGE 0x1060

/////////////////////////////////////////////////////////////////////////////
// CPSIA32Thread

IMPLEMENT_DYNCREATE(CPSIA32Thread, CWinThread)

CPSIA32Thread::CPSIA32Thread()
{
	m_recognizer = new PSIA32Recognizer();
}

CPSIA32Thread::~CPSIA32Thread()
{
	if (m_recognizer != NULL)
	{
		delete m_recognizer;
		m_recognizer = NULL;
	}
}

BOOL CPSIA32Thread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPSIA32Thread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPSIA32Thread, CWinThread)
	//{{AFX_MSG_MAP(CPSIA32Thread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_GUI_MESSAGE + 21, On_Output_Shellcode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSIA32Thread message handlers

LRESULT CPSIA32Thread::On_Output_Shellcode(WPARAM wParam, LPARAM lParam)
{
	PMParam *pParam = (PMParam *) wParam;
	PSShellcode *shellcode = (PSShellcode*) pParam->pObject1;
	delete pParam;
	pParam = NULL;
	
	if (shellcode == NULL || m_recognizer == NULL)
	{
		MyMessageBox_Error("On_Output_Shellcode");
		return 0;
	}
	
	m_nShellcodes.push_back(shellcode);
	m_recognizer->updateIPVs(shellcode);
	m_recognizer->updateICVs(shellcode);
	
	return 0;
}
