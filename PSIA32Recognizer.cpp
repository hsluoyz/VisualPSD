#include "StdAfx.h"

#include "PSIA32Recognizer.h"
#include "PSShellcode.h"

PSIA32Recognizer::PSIA32Recognizer()
{
	m_nMapIPVs.insert(pair<CString, int>("mov", 23));
	m_nMapIPVs.insert(pair<CString, int>("push", 12));
	m_nMapIPVs.insert(pair<CString, int>("cmp", 9));
	m_nMapIPVs.insert(pair<CString, int>("je", 6));
	m_nMapIPVs.insert(pair<CString, int>("add", 4));
	m_nMapIPVs.insert(pair<CString, int>("jne", 3));
	m_nMapIPVs.insert(pair<CString, int>("call", 3));
	m_nMapIPVs.insert(pair<CString, int>("jmp", 3));
	m_nMapIPVs.insert(pair<CString, int>("mov", 40));
	m_nMapIPVs.insert(pair<CString, int>("mov", 40));
	m_nMapIPVs.insert(pair<CString, int>("mov", 40));
}

int PSIA32Recognizer::getIPVByOpcode(CString strOpcode)
{
	int iIPV = m_nMapIPVs[strOpcode];
	if (iIPV <= 0)
	{
		MyMessageBox_Error("getIPVByOpcode");
		return -1;
	}
	else
	{
		return iIPV;
	}
}

int PSIA32Recognizer::getICVByDisasms(DISASM *pDisasm1, DISASM *pDisasm2)
{
	return 0;
}

void PSIA32Recognizer::updateIPVs(PSShellcode *shellcode)
{
	shellcode->nIPVs.clear();
	for (int i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		DISASM *pDisasm = shellcode->nDisasms[i];
		int iIPV = getIPVByOpcode(pDisasm->Instruction.Mnemonic);
		shellcode->nIPVs.push_back(iIPV);
	}
}

void PSIA32Recognizer::updateICVs(PSShellcode *shellcode)
{
	int i, j;
	shellcode->nnICVs.clear();

	vector<int> nICVs;
	for (i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		nICVs.push_back(-1);
	}
	for (i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		shellcode->nnICVs.push_back(nICVs);
	}

	for (i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		for (j = 0; j < shellcode->nDisasms.size(); j ++)
		{
			DISASM *pDisasm1 = shellcode->nDisasms[i];
			DISASM *pDisasm2 = shellcode->nDisasms[j];
			shellcode->nnICVs[i][j] = getICVByDisasms(pDisasm1, pDisasm2);
		}
	}
}