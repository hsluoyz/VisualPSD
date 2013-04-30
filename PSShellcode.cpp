#include "StdAfx.h"

#include "PSShellcode.h"

PSBlock::PSBlock()
{
	index = -1;
}

PSBlock::PSBlock(int iStart, int iEnd)
{
	start = iStart;
	end = iEnd;
	index = -1;
}

void PSBlock::addPreBlock(PSBlock *pBlock)
{
	npPreBlocks.push_back(pBlock);
}

void PSBlock::addNextBlock(PSBlock *pBlock)
{
	npNextBlocks.push_back(pBlock);
}

PSShellcode::PSShellcode(int packetNo, int shellcodeNo, BYTE *data, int size, int getPC)
{
	this->packetNo = packetNo;
	this->shellcodeNo = shellcodeNo;
	this->data = data;
	this->size = size;
	this->getPC = getPC;
	this->bPassIA32_1 = TRUE;
}
///*
DISASM* PSShellcode::addNewDisasm()
{
	DISASM *pBeaDisasm = new DISASM();
	memset(pBeaDisasm, 0, sizeof(DISASM));
	nDisasms.push_back(pBeaDisasm);
	return pBeaDisasm;
}
//*/
PSShellcode::~PSShellcode()
{
	free(data);
	///*
	for (int i = 0; i < nDisasms.size(); i ++)
	{
		if (nDisasms[i] != NULL)
		{
			delete nDisasms[i];
			nDisasms[i] = NULL;
		}
	}
	nDisasms.clear();
	//*/
}