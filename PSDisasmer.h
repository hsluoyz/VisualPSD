#include <vector>
using namespace std;

class PSShellcode;

class PSDisasmer
{
public:

public:
	PSDisasmer();
	CString itos(int i);
	int stoi(CString s);
	vector<CString> split(CString strTarget, CString strSeperate);
	int disasm(BYTE *pCode, int iSize, CString &strDump, CString &strText);
	void disasmShellcode(PSShellcode *shellcode, BOOL bEntire = FALSE);
	int getRandom(int iStart, int iScope);
	//void parseShellcodeDump(PSShellcode *shellcode);
	//void parseShellcodeText(PSShellcode *shellcode);
};