#pragma warning(disable:4786)
#include <vector>
#include <map>
using namespace std;

#define BEA_ENGINE_STATIC  /* specify the usage of a static version of BeaEngine */
#define BEA_USE_STDCALL    /* specify the usage of a stdcall version of BeaEngine */
#include <BeaEngine.h>

class PSShellcode;

class PSIA32Recognizer
{
public:
	map<CString, int> m_nMapIPVs;
public:
	PSIA32Recognizer();
	int getIPVByOpcode(CString strOpcode);
	int getICVByDisasms(DISASM *pDisasm1, DISASM *pDisasm2);
	void updateIPVs(PSShellcode *shellcode);
	void updateICVs(PSShellcode *shellcode);
	void verifyIA32();
};