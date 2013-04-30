#include "StdAfx.h"

#include "PSCFMAnalyzer.h"
#include "PSShellcode.h"

ALNode::ALNode(int iIndex)
{
	index = iIndex;
}
void ALNode::addPre(ALNode *node)
{
	pres.push_back(node);
}

void ALNode::addNext(ALNode *node)
{
	nexts.push_back(node);
}

void ALNode::removePre(ALNode *node)
{
	int iFound = 0;
	for (int i = 0; i < pres.size(); i ++)
	{
		if (pres[i] == node)
		{
			vector<ALNode*>::iterator iter = pres.begin();
			iter += i;
			pres.erase(iter);
			iFound = 1;
			break;
		}
	}
	if (iFound == 0)
	{
		MyMessageBox_Error("removePre");
	}

	for (i = 0; i < pres.size(); i ++)
	{
		if (pres[i] == node)
		{
			MyMessageBox_Error("removePre");
		}
	}
}

void ALNode::removeNext(ALNode *node)
{
	int iFound = 0;
	for (int i = 0; i < pres.size(); i ++)
	{
		if (nexts[i] == node)
		{
			vector<ALNode*>::iterator iter = nexts.begin();
			iter += i;
			nexts.erase(iter);
			iFound = 1;
			break;
		}
	}
	if (iFound == 0)
	{
		MyMessageBox_Error("removeNext");
	}
	
	for (i = 0; i < nexts.size(); i ++)
	{
		if (nexts[i] == node)
		{
			MyMessageBox_Error("removeNext");
		}
	}
}

PSCFMAnalyzer::PSCFMAnalyzer()
{
	m_ringGraph = NULL;
	m_ReachGraph = NULL;
}

BOOL PSCFMAnalyzer::checkSMCByDisasm(DISASM *pDisasm)
{
	if (pDisasm->Argument1.ArgType == MEMORY_TYPE && pDisasm->Argument1.AccessMode == WRITE)
	{
		if (pDisasm->Instruction.Mnemonic == "push")
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL PSCFMAnalyzer::checkControlByDisasm(DISASM *pDisasm)
{
	if (pDisasm->Instruction.BranchType != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL PSCFMAnalyzer::checkLoopBackBeforeDisasm(DISASM *pDisasm, DISASM *pPreDisasm)
{
	if (pDisasm->Instruction.AddrValue != 0)
	{
		int iAddrEIP = pDisasm->EIP;
		int iAddrJump = pDisasm->Instruction.AddrValue;
		int iAddrPreEIP = pPreDisasm->EIP;
		if (iAddrJump < iAddrPreEIP && iAddrPreEIP < iAddrEIP)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

void PSCFMAnalyzer::clearBlocks(PSShellcode *shellcode)
{
	shellcode->nBlocks.clear();
}

void PSCFMAnalyzer::splitBlocks(PSShellcode *shellcode)
{
	int iLastStart = 0;
	for (int i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		if (checkControlByDisasm(shellcode->nDisasms[i]))
		{
			PSBlock *pBlock = new PSBlock(iLastStart, i);
			shellcode->nBlocks.push_back(pBlock);
			iLastStart = i + 1;
		}
	}
	if (!checkControlByDisasm(shellcode->nDisasms[shellcode->nDisasms.size() - 1]))
	{
		PSBlock *pBlock = new PSBlock(iLastStart, shellcode->nDisasms.size() - 1);
		shellcode->nBlocks.push_back(pBlock);
	}

	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		shellcode->nBlocks[i]->startAddress = shellcode->nDisasms[shellcode->nBlocks[i]->start]->VirtualAddr;
		shellcode->nBlocks[i]->endAddress = shellcode->nDisasms[shellcode->nBlocks[i]->end]->VirtualAddr +
			shellcode->niDumpSizes[shellcode->nBlocks[i]->end] - 1;
	}
}

int PSCFMAnalyzer::getDisasmByAddress(PSShellcode *shellcode, int iAddress)
{
	int iDisasmIndex = -1;
	
	if (shellcode->nDisasms.size() == 0)
	{
		return -1;
	}
	else if (iAddress < shellcode->nDisasms[0]->VirtualAddr ||
		shellcode->nDisasms[shellcode->nDisasms.size() - 1]->VirtualAddr + shellcode->niDumpSizes[shellcode->nDisasms.size() - 1] <= iAddress)
	{
		return -1;
	}
	
	for (int i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		if (iAddress < shellcode->nDisasms[i]->VirtualAddr)
		{
			break;
		}
	}
	iDisasmIndex = i - 1;
	return iDisasmIndex;
}

void PSCFMAnalyzer::splitBlocksByAddress(PSShellcode *shellcode, int iAddress)
{
	int iDisasmToJump = getDisasmByAddress(shellcode, iAddress);
	if (iDisasmToJump < 0)
	{
		MyMessageBox_Error("splitBlocksByAddress");
	}
	else if (iAddress == shellcode->nDisasms[iDisasmToJump]->VirtualAddr)
	{
		splitBlocksByDisasm(shellcode, iDisasmToJump);
	}
	else
	{
		MyMessageBox_Error("splitBlocksByAddress");
	}
}

int PSCFMAnalyzer::getBlockByDisasm(PSShellcode *shellcode, int iDisasmIndex)
{
	int iBlockIndex = -1;
	for (int i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		if (shellcode->nBlocks[i]->start <= iDisasmIndex && iDisasmIndex <= shellcode->nBlocks[i]->end)
		{
			iBlockIndex = i;
		}
	}
	if (iBlockIndex == -1)
	{
		MyMessageBox_Error("getBlockIndexByDisasmIndex");
	}
	return iBlockIndex;
}

void PSCFMAnalyzer::splitBlocksByDisasm(PSShellcode *shellcode, int iDisasmIndex)
{
	int iBlockIndex = getBlockByDisasm(shellcode, iDisasmIndex);

	if (shellcode->nBlocks[iBlockIndex]->start != iDisasmIndex)
	{
		PSBlock *pBlock = shellcode->nBlocks[iBlockIndex];
		PSBlock *pBlock1 = new PSBlock();
		PSBlock *pBlock2 = new PSBlock();
		pBlock1->start = pBlock->start;
		pBlock1->startAddress = pBlock->startAddress;
		pBlock1->end = iDisasmIndex - 1;
		pBlock1->endAddress = shellcode->nDisasms[iDisasmIndex - 1]->VirtualAddr + shellcode->niDumpSizes[iDisasmIndex - 1] - 1;
		pBlock2->start = iDisasmIndex;
		pBlock2->startAddress = pBlock1->endAddress + 1;
		pBlock2->end = pBlock->end;
		pBlock2->endAddress = pBlock->endAddress;
		
		vector<PSBlock*>::iterator iter;
		iter = shellcode->nBlocks.begin();
		for (int i = 0; i < iBlockIndex; i ++)
		{
			iter ++;
		}
		shellcode->nBlocks.erase(iter);
		iter = shellcode->nBlocks.begin();
		for (i = 0; i < iBlockIndex; i ++)
		{
			iter ++;
		}
		shellcode->nBlocks.insert(iter, pBlock2);
		iter = shellcode->nBlocks.begin();
		for (i = 0; i < iBlockIndex; i ++)
		{
			iter ++;
		}
		shellcode->nBlocks.insert(iter, pBlock1);
		delete pBlock;
	}
}

void PSCFMAnalyzer::ResplitBlocks(PSShellcode *shellcode)
{
	for (int i = 0;  i < shellcode->nDisasms.size(); i ++)
	{
		DISASM *pDisasm = shellcode->nDisasms[i];
		if (pDisasm->Instruction.AddrValue != 0)
		{
			splitBlocksByAddress(shellcode, pDisasm->Instruction.AddrValue);
		}
	}
}

void PSCFMAnalyzer::prepareBlockRelations(PSShellcode *shellcode)
{
	for (int i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		PSBlock *pSrcBlock = shellcode->nBlocks[i];
		DISASM *pLastDisasm = shellcode->nDisasms[shellcode->nBlocks[i]->end];
		if (pLastDisasm->Instruction.AddrValue != 0)
		{
			int iDestDisasm = getDisasmByAddress(shellcode, pLastDisasm->Instruction.AddrValue);
			PSBlock *pDestBlock = shellcode->nBlocks[getBlockByDisasm(shellcode, iDestDisasm)];
			pSrcBlock->addNextBlock(pDestBlock);
			pDestBlock->addPreBlock(pSrcBlock);
		}
	}
}

void PSCFMAnalyzer::updateGetPCDisasm(PSShellcode *shellcode)
{
	if (shellcode->nDisasms.size() != 0)
	{
		int iGetPCAddress = shellcode->nDisasms[0]->VirtualAddr + shellcode->getPC;
		int iDisasmIndex = getDisasmByAddress(shellcode, iGetPCAddress);
		shellcode->iGetPCDisasm = iDisasmIndex;
	}
}

void PSCFMAnalyzer::updateSMCDisasms(PSShellcode *shellcode)
{
	shellcode->niSMCDisasms.clear();
	for (int i = 0; i < shellcode->nDisasms.size(); i ++)
	{
		DISASM *pDisasm = shellcode->nDisasms[i];
		if (checkSMCByDisasm(pDisasm))
		{
			shellcode->niSMCDisasms.push_back(i);
		}
	}
}

void PSCFMAnalyzer::labelDisasmsAndBlocks(PSShellcode *shellcode)
{
	int i;

	//for (i = 0; i < shellcode->nDisasms.size(); i ++)
	//{
	//	shellcode->nDisasms[i]->index = i;
	//}

	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		shellcode->nBlocks[i]->index = i;
	}
}

BOOL PSCFMAnalyzer::checkRing(PSShellcode *shellcode, int iNode)
{
	if (m_ringGraph)
	{
		delete m_ringGraph;
		m_ringGraph = new RingGraph();
	}

	m_ringGraph->initALNodes(shellcode);
	m_ringGraph->performTopologicalSort(shellcode);
	BOOL bResult = m_ringGraph->checkRing(iNode);
	return bResult;
}

BOOL PSCFMAnalyzer::checkReach(PSShellcode *shellcode, int iStart, int iEnd)
{
	if (m_ReachGraph)
	{
		delete m_ReachGraph;
		m_ReachGraph = new ReachGraph();
	}

	m_ReachGraph->initReachGraph(shellcode);
	m_ReachGraph->calculate(iStart);
	BOOL bResult = m_ReachGraph->queryResult(iEnd);
	return bResult;
}

int RingGraph::getBlockByDisasm(PSShellcode *shellcode, int iDisasmIndex)
{
	int iBlockIndex = -1;
	for (int i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		if (shellcode->nBlocks[i]->start <= iDisasmIndex && iDisasmIndex <= shellcode->nBlocks[i]->end)
		{
			iBlockIndex = i;
		}
	}
	if (iBlockIndex == -1)
	{
		MyMessageBox_Error("getBlockIndexByDisasmIndex");
	}
	return iBlockIndex;
}

void RingGraph::clearALNodes()
{
	for (int i = 0; i < m_nALNodes.size(); i ++)
	{
		delete m_nALNodes[i];
	}
	m_nALNodes.clear();
	m_iGetPCNode = -1;
	m_niSMCNodes.clear();
}

void RingGraph::initALNodes(PSShellcode *shellcode)
{
	int i, j;
	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		ALNode *alNode = new ALNode(i);
		m_nALNodes.push_back(alNode);
	}

	for (i = 0; i < m_nALNodes.size(); i ++)
	{
		PSBlock *pSrcBlock = shellcode->nBlocks[i];

		for (j = 0; j < pSrcBlock->npPreBlocks.size(); j ++)
		{
			PSBlock *pDestBlock = pSrcBlock->npPreBlocks[j];
			m_nALNodes[i]->addPre(m_nALNodes[pDestBlock->index]);
		}

		for (j = 0; j < pSrcBlock->npNextBlocks.size(); j ++)
		{
			PSBlock *pDestBlock = pSrcBlock->npNextBlocks[j];
			m_nALNodes[i]->addNext(m_nALNodes[pDestBlock->index]);
		}
	}

	PSBlock *pGetPCBlock = shellcode->nBlocks[getBlockByDisasm(shellcode, shellcode->iGetPCDisasm)];
	m_iGetPCNode = pGetPCBlock->index;
	for (i = 0; i < shellcode->niSMCDisasms.size(); i ++)
	{
		int iBlock = getBlockByDisasm(shellcode, shellcode->niSMCDisasms[i]);
		int iFlag = 0;
		for (j = 0; j < m_niSMCNodes.size(); j ++)
		{
			if (m_niSMCNodes[j] == iBlock)
			{
				iFlag = 1;
				break;
			}
		}
		if (iFlag == 0)
		{
			m_niSMCNodes.push_back(iBlock);
		}
	}
}

void RingGraph::removeALNode(ALNode *pALNode)
{
	int i;
	vector<ALNode*>::iterator iter = m_nALNodes.begin();
	iter += pALNode->index;
	m_nALNodes.erase(iter);

	for (i = 0; i < pALNode->pres.size(); i ++)
	{
		pALNode->pres[i]->removeNext(pALNode);
	}
	for (i = 0; i < pALNode->nexts.size(); i ++)
	{
		pALNode->nexts[i]->removePre(pALNode);
	}

	delete pALNode;
}

void RingGraph::performTopologicalSort(PSShellcode *shellcode)
{
	int iChange;
	do 
	{
		iChange = 0;
		for (int i = 0; i < m_nALNodes.size(); i ++)
		{
			if (m_nALNodes[i]->pres.size() == 0)
			{
				removeALNode(m_nALNodes[i]);
				i = 0;
				iChange = 1;
			}
		}
	}
	while (iChange);
}

BOOL RingGraph::checkRing(int iNode)
{
	for (int i = 0; i < m_nALNodes.size(); i ++)
	{
		if (m_nALNodes[i]->index == iNode)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void ReachGraph::initReachGraph(PSShellcode *shellcode)
{
	nniArcs.clear();
	vector<int> niArcsRow;
	int i, j;

	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		niArcsRow.push_back(MGRAPH_MAX_DIST);
	}
	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		nniArcs.push_back(niArcsRow);
	}

	for (i = 0; i < shellcode->nBlocks.size(); i ++)
	{
		PSBlock *pSrcBlock = shellcode->nBlocks[i];
		for (j = 0;  j < pSrcBlock->npNextBlocks.size(); j ++)
		{
			PSBlock *pDestBlock = pSrcBlock->npNextBlocks[j];
			nniArcs[pSrcBlock->index][pDestBlock->index] = 1;
		}
	}
}

void ReachGraph::calculate(int iStart)
{
	this->iStart = iStart;
	s.clear();
	path.clear();
	dist.clear();

	int i,j,v0,min,u,n;
	v0 = iStart;
	n = iCntNodes;
	cost = nniArcs; //cost矩阵初始化

	for (i = 0; i < n; i ++)
	{
		dist.push_back(cost[v0][i]); //dist数组初始化
		path.push_back(-1); //path数组初始化
		if (dist[i] < MGRAPH_MAX_DIST && dist[i] > 0)
		{
			path[i] = v0;
		}
	}

	for (i = 0; i < n; i ++)
	{
		s.push_back(0);
	}
	s[v0]=1;

	for (i = 0; i < n; i ++) //按最短路径递增算法
	{
		min = MGRAPH_MAX_DIST;
		u = v0;
		for (j = 0; j < n; j ++)
		{
		   if (s[j] == 0 && dist[j] < min)
		   {
			   min=dist[j];
			   u = j;
		   }
		}
		s[u] = 1; //u顶点是求得的最短路径的顶点编号
		for (j = 0; j < n; j++) //求最短路径重复进行下述操作n-1次
		   if (s[j] == 0 && dist[u] + cost[u][j] < dist[j]) //调整dist如果dist[u]+cost[u][j]<dist[j]则执行下一句
		   {
			   dist[j] = dist[u] + cost[u][j];
			   path[j] = u; //path记录了路径经过的顶点
		   }
	}

}

BOOL ReachGraph::queryResult(int iEnd)
{
	result.clear();
	int i = iEnd;
	int u;
	int v0 = iStart;

	if (s[i] == 1)
	{
		u = i;
		while (u != v0)
		{
			result.push_back(u);
			u = path[u];
		}
		printf("%d",u+1);
		result.push_back(u);
		return TRUE; //有路径，长度dist[i]
	}
	else
	{
		return FALSE; //无路径
	}
}
