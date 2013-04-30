#include <vector>
using namespace std;

class PSNIC;

class PSSimpleNIC
{
public:
	CString ip;
	CString mac;
public:
	PSSimpleNIC(CString strIP);
	CString retrieveMacFromIP(CString strIP);
};

class PSForwarder
{
public:
	vector<PSNIC*> m_npNICs;
	vector<PSSimpleNIC*> m_npHostNICs;
	vector<PSSimpleNIC*> m_npVMNICs;
	PSSimpleNIC *pRelayNIC;
	CString m_strDataDirectory;
	
public:
	PSForwarder(CString strRelayIP, vector<PSNIC*> npNICs);
	~PSForwarder();
	static BOOL checkIP(CString strIP);
	BOOL FolderExist(CString strPath);
	void initDataDir();
	void clearSimpleNICs();
	void readListFromFile();
	
};