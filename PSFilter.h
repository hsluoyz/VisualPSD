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

typedef struct _IPHeader                    // 20字节的IP头
{
    UCHAR     iphVerLen;          // 4位首部长度+4位IP版本号            | Version (4 bits) + Internet header length (4 bits)
    UCHAR     ipTOS;                 // 8位服务类型                                    | TOS Type of service
    USHORT    ipLength;             // 16位封包总长度，即整个IP报的长度   | Total length
    USHORT    ipID;                    // 16位封包标识，惟一标识发送的每一个数据报      | Identification
    USHORT    ipFlags;              // 3位标志位+13报片偏移                 | Flags (3 bits) + Fragment offset (13 bits)
    UCHAR     ipTTL;                 // 8位生存时间，就是TTL                 | Time to live
    UCHAR     ipProtocol;            // 8位协议，TCP、UDP、ICMP等          | Protocol
    USHORT    ipChecksum;    // 16位IP首部校验和                   | Header checksum
    ULONG     ipSource;          // 32位源IP地址                       | Source address
    ULONG     ipDestination;            // 32位目标IP地址                     | Destination address
} IPHeader, *PIPHeader;

typedef struct _TCPHeader          // 20字节的TCP头
{
	USHORT sourcePort;           // 16位源端口号    | Source port
	USHORT destinationPort;      // 16位目的端口号 | Destination port
	ULONG sequenceNumber;       // 32位序列号      | Sequence Number
	ULONG acknowledgeNumber;    // 32位确认号      | Acknowledgement number
	UCHAR   dataoffset;                        // 高4位表示数据偏移，低6位保留字 | Header length
	UCHAR   flags;                  // 6位标志位       | packet flags
	USHORT windows;                    // 16位窗口大小    | Window size
	USHORT checksum;                  // 16位校验和      | Header Checksum
	USHORT urgentPointer;        // 16位紧急数据偏移量   | Urgent pointer...still don't know what this is...
} TCPHeader, *PTCPHeader;

typedef struct _UDPHeader
{
	USHORT               sourcePort;           // 16位源端口号   | Source port
	USHORT               destinationPort;      // 16位目的端口号 | Destination port     
	USHORT               len;                  // 16位封包长度   | Sequence Number
	USHORT               checksum;             // 16位校验和     | Acknowledgement number
} UDPHeader, *PUDPHeader;




CString protocol2String(int iProtocolType);
CString protocol2String2(int iProtocolType);