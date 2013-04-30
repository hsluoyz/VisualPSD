#include "StdAfx.h"

#include "PSDisasmer.h"
#include "PSShellcode.h"
#include "disasm.h"

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */
#include <BeaEngine.h>

#include <stdlib.h>

PSDisasmer::PSDisasmer()
{
	srand((int) time(0));
}

CString PSDisasmer::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

int PSDisasmer::stoi(CString s)
{
	return atoi(s);
}

vector<CString> PSDisasmer::split(CString strTarget, CString strSeperate)
{
	CString strTemp=strTarget;
	vector<CString> nStrResult;
	while (true)
	{
		CString n = strTemp.SpanExcluding(strSeperate);
		nStrResult.push_back(n);
		strTemp = strTemp.Right(strTemp.GetLength() - n.GetLength() - 1);
		if (strTemp.IsEmpty())
		{
			break;
		}
	}
	return nStrResult;
}

/*
void PSDisasmer::parseShellcodeDump(PSShellcode *shellcode)
{
	shellcode->niDumpOffsets.clear();
	shellcode->niDumpOffsets.push_back(0);

	for (int i = 1; i < shellcode->size - 1; i ++)
	{
		if (shellcode->data[i] == ' ')
		{
			shellcode->niDumpOffsets.push_back(i);
		}
	}
}

void PSDisasmer::parseShellcodeText(PSShellcode *shellcode)
{
	shellcode->nstrInstructions = split(shellcode->strText, "\n");
}
*/

int PSDisasmer::disasm(BYTE *pCode, int iSize, CString &strDump, CString &strText)
{
	t_disasm da;
	int iSizeDisasmed = Disasm((char*) pCode, iSize, 0x00400000, &da, DISASM_CODE);

	strDump.Format("%s", da.dump);
	strText = da.result;
	return iSizeDisasmed;
}

void PSDisasmer::disasmShellcode(PSShellcode *shellcode, BOOL bEntire)
{
	int iStart, iEnd;
	if (bEntire)
	{
		iStart = 0;
		iEnd = shellcode->size;
	}
	else
	{
		iStart = getRandom(0, shellcode->getPC / 2);
		iEnd = min(shellcode->getPC + 10, shellcode->size);
	}

	int iSizeTotalDisasmed = 0;
	int iSizeDisasmed = -1;
	CString strIsCode = "Yes";
	int i;
	
	CString strDump;
	CString strText;
	int len;
	int Error = 0;

	do 
	{
		iSizeDisasmed = disasm(shellcode->data + iStart + iSizeTotalDisasmed, 20, strDump, strText);
		
		DISASM *pBeaDisasm = shellcode->addNewDisasm();
		pBeaDisasm->EIP = (UIntPtr) (shellcode->data + iStart + iSizeTotalDisasmed);
		len = Disasm(pBeaDisasm);

		if (strText == "???")
		{
			strIsCode = "No";
			shellcode->bPassIA32_1 = FALSE;
			break;
		}
		
		if (iSizeTotalDisasmed + iSizeDisasmed > iEnd - iStart)
		{
			break;
		}
		else
		{
			shellcode->niDumpOffsets.push_back(iSizeTotalDisasmed);
			shellcode->niDumpSizes.push_back(iSizeDisasmed);
			shellcode->nstrDump.push_back(strDump);
			shellcode->nstrText.push_back(strText);
		}

		iSizeTotalDisasmed += iSizeDisasmed;
	}
	while (iSizeTotalDisasmed < iEnd - iStart);

	char strTmp[512];
	sprintf(strTmp, "[Sequence No.]:%5d  [Length]:%4d  [Start Offset]:%4d  [End Offset]:%4d\r\n[Disasmed Size]:%4d  [Is Code?]:%s\n",
		shellcode->shellcodeNo, shellcode->size, iStart, iEnd, iSizeTotalDisasmed, strIsCode);
	Output_IA32_List(itos(shellcode->shellcodeNo), strTmp);

	///*
	Output_Dump_EditBox("***********************************************************");
	Output_Dump_EditBox(strTmp);

	CString cstrTemp;

	cstrTemp = "";
	for (i = 0; i < shellcode->nstrDump.size(); i ++)
	{
		cstrTemp += "\r\n";
		cstrTemp += shellcode->nstrDump[i];
	}
	Output_Dump_EditBox(cstrTemp);
	Output_Dump_EditBox("***********************************************************\r\n");


	Output_Text_EditBox("***********************************************************");
	Output_Text_EditBox(strTmp);

	cstrTemp = "";
	for (i = 0; i < shellcode->nstrText.size(); i ++)
	{
		cstrTemp += "\r\n";
		cstrTemp += shellcode->nstrText[i];
	}
	Output_Text_EditBox(cstrTemp);
	Output_Text_EditBox("***********************************************************\r\n");
	//*/

	//parseShellcodeDump(shellcode);
	//parseShellcodeText(shellcode);
}

int PSDisasmer::getRandom(int iStart, int iScope)
{
	return iStart + (iScope - iStart) * rand() / (RAND_MAX + 1.0);
}

