#ifndef _CLASS_PMPARAM
#define  _CLASS_PMPARAM

class PSShellcode;

class PMParam
{
public:
	CString strParam1;
	CString strParam2;
	void *pObject1;
public:
	PMParam(CString strParam1);
	PMParam(CString strParam1, CString strParam2);
	PMParam(void *pObject1);
};

#endif

void MyMessageBox_Error(CString strText, CString strCaption);
void MyMessageBox_Error(CString strFunction);
void Output_Packets_List(CString strNo, CString strContent);
void Output_GetPC_List(CString strNo, CString strContent);
void Output_IA32_List(CString strNo, CString strContent);
void Output_CFM_List(CString strNo, CString strContent);
void Output_DFM_List(CString strNo, CString strContent);

void Output_Dump_EditBox(CString strContent);
void Output_Text_EditBox(CString strContent);
void Output_Shellcode(PSShellcode *shellcode);