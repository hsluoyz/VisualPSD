#include <pcap.h>
#include <vector>
using namespace std;

#define PACKET_IPV4 0
#define PACKET_ARP 1
#define PACKET_IPV6 2
#define PACKET_ICMP 3
#define PACKET_IGMP 4
#define PACKET_TCP 5
#define PACKET_UDP 6
#define PACKET_UNKNOWN 7

#define GETPC1 0xE8
#define GETPC2 0xD9

class PSShellcode;

class PSNIC
{
public:
	int winpcap_index;
	int iphlp_index;
	CString winpcap_name;
	CString iphlp_name;
	CString desc;
	CString mac;
	CString ip;
	CString subnet;
	CString broadcast;
public:
	PSNIC(int no, CString name, CString desc)
	{
		this->winpcap_index = no;
		this->winpcap_name = name;
		this->desc = desc;
	}
};

class PSFilter
{
public:
	int m_iPacketNo;
	int m_iShellcodeNo;
	BOOL m_bStop;
	BOOL m_bReserveNICs;
	vector<PSNIC*> m_nNICs;
	pcap_t *m_hDestNIC;
	vector<int> m_niIndice;
	vector<CString> m_nstrAdapterNames;

public:
	PSFilter();
	~PSFilter();
	CString itos(int i);
	int stoi(CString s);
	void setReserveNICs(BOOL bReserveNICs);
	void expandString(char *s, int iDigits);
	void Simple_Output_Packets_List(CString strContent);
	void Simple_Output_Packets_List_Without_Increment(CString strContent);
	void Simple_Output_GetPC_List(CString strContent);
	void Simple_Output_GetPC_List_Without_Increment(CString strContent);
	void stop();
	char* iptos(u_long in);
	void listIPs(pcap_if_t *d);
	CString getMacByWinPcapName(CString strAdapterName);
	void getAdapterIndice();
	BOOL searchAdapterIndexAndName(PSNIC *pNIC);
	BOOL isIdenticalNICName(CString strNICName1, CString strNICName2);
	BOOL listIPInfos();
	BOOL listNICs(BOOL bDisplay = TRUE);
	int captureNIC(int iSrcNICNo, int iDestNICNo = -1);
	int forwardPacket(pcap_t *hAdapter, BYTE *byPacketData, int iSize);
	int parsePacket(BYTE *byPacketData, int iSize, CString &strDesc);
	void extractPacket(BYTE *pData, int cbData);
};

#define ETHER_ADDR_LEN 6
#define ETHER_HEADER_LENGTH 14
#define TCP_HEADER_LENGTH 20
#define UDP_HEADER_LENGTH 20

typedef struct _EthernetHeader
{
	UCHAR  dhost[ETHER_ADDR_LEN];
	UCHAR  shost[ETHER_ADDR_LEN];
	USHORT type;
} EthernetHeader, *PEthernetHeader;

typedef struct _IPHeader                    // 20�ֽڵ�IPͷ
{
    UCHAR     iphVerLen;          // 4λ�ײ�����+4λIP�汾��            | Version (4 bits) + Internet header length (4 bits)
    UCHAR     ipTOS;                 // 8λ��������                                    | TOS Type of service
    USHORT    ipLength;             // 16λ����ܳ��ȣ�������IP���ĳ���   | Total length
    USHORT    ipID;                    // 16λ�����ʶ��Ωһ��ʶ���͵�ÿһ�����ݱ�      | Identification
    USHORT    ipFlags;              // 3λ��־λ+13��Ƭƫ��                 | Flags (3 bits) + Fragment offset (13 bits)
    UCHAR     ipTTL;                 // 8λ����ʱ�䣬����TTL                 | Time to live
    UCHAR     ipProtocol;            // 8λЭ�飬TCP��UDP��ICMP��          | Protocol
    USHORT    ipChecksum;    // 16λIP�ײ�У���                   | Header checksum
    ULONG     ipSource;          // 32λԴIP��ַ                       | Source address
    ULONG     ipDestination;            // 32λĿ��IP��ַ                     | Destination address
} IPHeader, *PIPHeader;

typedef struct _TCPHeader          // 20�ֽڵ�TCPͷ
{
	USHORT sourcePort;           // 16λԴ�˿ں�    | Source port
	USHORT destinationPort;      // 16λĿ�Ķ˿ں� | Destination port
	ULONG sequenceNumber;       // 32λ���к�      | Sequence Number
	ULONG acknowledgeNumber;    // 32λȷ�Ϻ�      | Acknowledgement number
	UCHAR   dataoffset;                        // ��4λ��ʾ����ƫ�ƣ���6λ������ | Header length
	UCHAR   flags;                  // 6λ��־λ       | packet flags
	USHORT windows;                    // 16λ���ڴ�С    | Window size
	USHORT checksum;                  // 16λУ���      | Header Checksum
	USHORT urgentPointer;        // 16λ��������ƫ����   | Urgent pointer...still don't know what this is...
} TCPHeader, *PTCPHeader;

typedef struct _UDPHeader
{
	USHORT               sourcePort;           // 16λԴ�˿ں�   | Source port
	USHORT               destinationPort;      // 16λĿ�Ķ˿ں� | Destination port     
	USHORT               len;                  // 16λ�������   | Sequence Number
	USHORT               checksum;             // 16λУ���     | Acknowledgement number
} UDPHeader, *PUDPHeader;




CString protocol2String(int iProtocolType);
CString protocol2String2(int iProtocolType);