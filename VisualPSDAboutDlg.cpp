// VisualPSDAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPSD.h"
#include "VisualPSDAboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDAboutDlg dialog


CVisualPSDAboutDlg::CVisualPSDAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVisualPSDAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPSDAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVisualPSDAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPSDAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_EDIT, m_editAbout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisualPSDAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CVisualPSDAboutDlg)
	ON_BN_CLICKED(IDC_COMPANY_URL, OnCompanyUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPSDAboutDlg message handlers

BOOL CVisualPSDAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	SetWindowText(_T("����VisualPSD"));
	CString strText;
	strText += _T("VisualPSD v1.0.0����Visual C++ 6.0���������BCGControlBar Pro 18.0��WinPcap 4.1.2������ɡ�\r\n");
	strText += _T("֧��Windows�汾������汾����Windows XP/Vista/7���������������Windows Server 2003/2008/2008 R2��Windows 2000/NT4/9x�Ȼ����ᱻ�Զ����ԡ�\r\n");
	strText += _T("ʹ��ǰ���Ȱ�װWinPcap 4.1.2������°汾��\r\n");
	strText += _T("\r\n");
	strText += _T("ʹ�÷�����\r\n");
	strText += _T("��ѡ��һ̨������ͬһ�������ļ������װ����������Բ��������ڼ������������������\r\n");
	strText += _T("���ڡ������Ա��¼��������������������ơ������Ա�˻�����󣬵������¼����ť���ȴ�����Ϣ��ͼ�η�ʽ��ʾ����������������϶���\r\n");
	strText += _T("�۵�����������桱��ť�����������߼��������棻\r\n");
	strText += _T("�ܵ������ͻ��⡱��ť���ȴ�һ��ʱ�䣬�����Գ�ͻ����������򽫻���ʾ���д��ڵľ����ͻ������ϸ˵����\r\n");
	strText += _T("�����ͼ�η����ڵ����������й��ڽ��ܣ������á����ģʽ������ġ��༭ͼ��Ԫ�ء����ܣ���ʱ��������ͼ�ε�λ�úʹ�С��\r\n");
	strText += _T("���ڷǱ༭ģʽ�µ����û����顢�������Ԫ��ʱ���Ҳ�������������ʾ�������Ϣ����չ��Ϣ��\r\n");
	strText += _T("�������Ҫ������һ�ε�¼�ͼ�⣬һ��Ҫ�ȵ������ջ��桱��ť������һ�ε���Ϣȫ�������\r\n");
	strText += _T("\r\n");
	strText += _T("����֧������ϵ��veotax@sae.buaa.edu.cn\r\n");
	strText += _T("                                                                                                                  2012/7/13\r\n");
	m_editAbout.SetWindowText(strText);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVisualPSDAboutDlg::OnCompanyUrl() 
{
	ShellExecute(NULL, _T("open"), _T("http://www.buaa.edu.cn"), NULL, NULL, SW_MAXIMIZE);
}
