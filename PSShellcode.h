#include <vector>
using namespace std;

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */
#include <BeaEngine.h>

class PSBlock
{
public:
	int start;
	int end;
	int startAddress;
	int endAddress;
	vector<PSBlock*> npPreBlocks;
	vector<PSBlock*> npNextBlocks;
	int index;
public:
	PSBlock();
	PSBlock(int iStart, int iEnd);
	void addPreBlock(PSBlock *pBlock);
	void addNextBlock(PSBlock *pBlock);
};

class PSShellcode
{
public:
	int packetNo;
	int shellcodeNo;
	BYTE *data;
	int size;
	int getPC;
	
	vector<int> niDumpOffsets;
	vector<int> niDumpSizes;
	vector<CString> nstrDump;
	vector<CString> nstrText;
	vector<DISASM*> nDisasms;

	BOOL bPassIA32_1;
	BOOL bPassIA32_2;
	vector<int> nIPVs;
	vector<vector<int> > nnICVs;

	vector<PSBlock*> nBlocks;
	int iGetPCDisasm;
	vector<int> niSMCDisasms;

public:
	PSShellcode(int packetNo, int shellcodeNo, BYTE *data, int size, int getPC);
	DISASM* addNewDisasm();
	~PSShellcode();
};