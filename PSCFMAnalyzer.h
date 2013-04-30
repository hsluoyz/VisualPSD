#include <vector>
using namespace std;

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */
#include <BeaEngine.h>

class PSShellcode;
class PSBlock;

class ALNode
{
public:
	int index;
	vector<ALNode*> pres;
	vector<ALNode*> nexts;
	ALNode(int iIndex);
	void addPre(ALNode *node);
	void addNext(ALNode *node);
	void removePre(ALNode *node);
	void removeNext(ALNode *node);
};

class RingGraph
{
public:
	vector<ALNode*> m_nALNodes;
	int m_iGetPCNode;
	vector<int> m_niSMCNodes;

public:
	int getBlockByDisasm(PSShellcode *shellcode, int iDisasmIndex);
	void clearALNodes();
	void initALNodes(PSShellcode *shellcode);
	void removeALNode(ALNode *pALNode);
	void performTopologicalSort(PSShellcode *shellcode);
	BOOL checkRing(int iNode);
};

#define MGRAPH_MAX_DIST 10000

class ReachGraph
{
public:
	int iCntNodes;
	int iStart;
	vector<vector<int> > nniArcs;
	vector<vector<int> > cost;
	
	vector<int> s;
	vector<int> path;
	vector<int> dist;
	
	vector<int> result;
	
public:
	void initReachGraph(PSShellcode *shellcode);
	void calculate(int iStart);
	BOOL queryResult(int iEnd);
};

class PSCFMAnalyzer
{
public:
	RingGraph *m_ringGraph;
	ReachGraph *m_ReachGraph;
public:
	PSCFMAnalyzer();
	BOOL checkSMCByDisasm(DISASM *pDisasm);
	BOOL checkControlByDisasm(DISASM *pDisasm);
	BOOL checkLoopBackBeforeDisasm(DISASM *pDisasm, DISASM *pPreDisasm);
	void clearBlocks(PSShellcode *shellcode);
	void splitBlocks(PSShellcode *shellcode);
	int getDisasmByAddress(PSShellcode *shellcode, int iAddress);
	void splitBlocksByAddress(PSShellcode *shellcode, int iAddress);
	int getBlockByDisasm(PSShellcode *shellcode, int iDisasmIndex);
	void splitBlocksByDisasm(PSShellcode *shellcode, int iDisasmIndex);
	void ResplitBlocks(PSShellcode *shellcode);
	void prepareBlockRelations(PSShellcode *shellcode);

	void updateGetPCDisasm(PSShellcode *shellcode);
	void updateSMCDisasms(PSShellcode *shellcode);

	void labelDisasmsAndBlocks(PSShellcode *shellcode);
	
	BOOL checkRing(PSShellcode *shellcode, int iNode);
	BOOL checkReach(PSShellcode *shellcode, int iStart, int iEnd);
};