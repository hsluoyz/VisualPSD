#include "StdAfx.h"

#include "PSFilter.h"
#include "PSShellcode.h"

#include <packet32.h>

#include <Iphlpapi.h>

CString protocol2String(int iProtocolType)
{
	if (iProtocolType == PACKET_IPV4)
		return "IPv4";
	else if (iProtocolType == PACKET_ARP)
		return "ARP&RARP";
	else if (iProtocolType == PACKET_IPV6)
		return "IPv6";
	else if (iProtocolType == PACKET_ICMP)
		return "ICMP";
	else if (iProtocolType == PACKET_IGMP)
		return "IGMP";
	else if (iProtocolType == PACKET_TCP)
		return "TCP";
	else if (iProtocolType == PACKET_UDP)
		return "UDP";
	else if (iProtocolType == PACKET_UNKNOWN)
		return "Unknown";
	else
		return "Unknown";
}

CString protocol2String2(int iProtocolType)
{
	if (iProtocolType == PACKET_IPV4)
		return "IPv4     ";
	else if (iProtocolType == PACKET_ARP)
		return "ARP&RARP ";
	else if (iProtocolType == PACKET_IPV6)
		return "IPv6     ";
	else if (iProtocolType == PACKET_ICMP)
		return "ICMP     ";
	else if (iProtocolType == PACKET_IGMP)
		return "IGMP     ";
	else if (iProtocolType == PACKET_TCP)
		return "TCP      ";
	else if (iProtocolType == PACKET_UDP)
		return "UDP      ";
	else if (iProtocolType == PACKET_UNKNOWN)
		return "Unknown  ";
	else
		return "Unknown  ";
}

PSFilter::PSFilter()
{
	m_iPacketNo = 0;
	m_iShellcodeNo = 0;
	m_bStop = FALSE;
	m_hDestNIC = NULL;
}

PSFilter::~PSFilter()
{
	if (!m_bReserveNICs)
	{
		for (int i = 0; i < m_nNICs.size(); i ++)
		{
			if (m_nNICs[i])
			{
				delete m_nNICs[i];
			}
		}
		m_nNICs.clear();
	}
}

CString PSFilter::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

int PSFilter::stoi(CString s)
{
	return atoi(s);
}

void PSFilter::setReserveNICs(BOOL bReserveNICs)
{
	m_bReserveNICs = bReserveNICs;
}

void PSFilter::expandString(char *s, int iDigits)
{
	for (int i = 0; i < iDigits; i ++)
	{
		if (s[i] == '\0')
			s[i] = ' ';
	}
	s[16] = '\0';
}

void PSFilter::Simple_Output_Packets_List(CString strContent)
{
	Output_Packets_List(itos(m_iPacketNo ++), strContent);
}

void PSFilter::Simple_Output_Packets_List_Without_Increment(CString strContent)
{
	Output_Packets_List(itos(m_iPacketNo), strContent);
}

void PSFilter::Simple_Output_GetPC_List(CString strContent)
{
	Output_GetPC_List(itos(m_iShellcodeNo ++), strContent);
}

void PSFilter::Simple_Output_GetPC_List_Without_Increment(CString strContent)
{
	Output_GetPC_List(itos(m_iShellcodeNo), strContent);
}

void PSFilter::stop()
{
	m_bStop = TRUE;
}

#define IPTOSBUFFERS 12  
char* PSFilter::iptos(u_long in)
{  
	static char output[IPTOSBUFFERS][3*4+3+1];  
	static short which;  
	u_char *p;  
	
	p = (u_char *)&in;  
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);  
	sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);  
	return output[which];  
} 

void PSFilter::listIPs(pcap_if_t *pAdapter)
{
	char strTmp[1024];

	pcap_addr_t *pAddresses;  
	
	/* 回环地址 */  
	sprintf(strTmp, "[LoopBack]: %s\n",(pAdapter->flags & PCAP_IF_LOOPBACK)?"Yes":"No");  
	Simple_Output_Packets_List_Without_Increment(strTmp);
	/* IP 地址 */  
	for (pAddresses=pAdapter->addresses;pAddresses;pAddresses=pAddresses->next)
	{  
		sprintf(strTmp, "[Address Family]: %d\n",pAddresses->addr->sa_family);
		Simple_Output_Packets_List_Without_Increment(strTmp);
		
		switch(pAddresses->addr->sa_family)  
		{  
		case AF_INET:  
			sprintf(strTmp, "[Address Family Name]: AF_INET\n");
			Simple_Output_Packets_List_Without_Increment(strTmp);
			if (pAddresses->addr)  
				/* Y- IP 地址 */  
				sprintf(strTmp, "[Address]: %s\n",iptos(((struct sockaddr_in *)pAddresses->addr)->sin_addr.s_addr));  
			if (pAddresses->netmask)  
				/* Y- 掩码 */  
				sprintf(strTmp, "[Netmask]: %s\n",iptos(((struct sockaddr_in *)pAddresses->netmask)->sin_addr.s_addr));  
			if (pAddresses->broadaddr)  
				/* Y- 广播地址 */  
				sprintf(strTmp, "[Broadcast Address]: %s\n",iptos(((struct sockaddr_in *)pAddresses->broadaddr)->sin_addr.s_addr));  
			if (pAddresses->dstaddr)  
				/* Y - 目标地址 */  
				sprintf(strTmp, "[Destination Address]: %s\n",iptos(((struct sockaddr_in *)pAddresses->dstaddr)->sin_addr.s_addr));  
			Simple_Output_Packets_List_Without_Increment(strTmp);
			break;  
		default:  
			/* 未知 */  
			sprintf(strTmp, "[Address Family Name]: Unknown\n");
			Simple_Output_Packets_List_Without_Increment(strTmp);
			break;  
		}  
	}  
}

#define   OID_802_3_CURRENT_ADDRESS	0x01010102
CString PSFilter::getMacByWinPcapName(CString strAdapterName)
{
	char strTmp[1024];
	LPADAPTER hAdapter;
	unsigned char mac[6];
	
	strcpy(strTmp, strAdapterName.GetBuffer(0));
	hAdapter = PacketOpenAdapter(strTmp + 8);
	if (hAdapter == NULL)
	{
		MyMessageBox_Error("getMacByWinPcapName");
		return "";
	}
	PPACKET_OID_DATA OidData = (PPACKET_OID_DATA) malloc(512);
	if (OidData == NULL)
	{
		MyMessageBox_Error("getMacByWinPcapName");
		return "";
	}
	
	OidData-> Oid = OID_802_3_CURRENT_ADDRESS;
	OidData-> Length = 256;
	ZeroMemory(OidData->Data, 256);
	if (!PacketRequest(hAdapter, FALSE, OidData))
	{
		free(OidData);
		MyMessageBox_Error("getMacByWinPcapName");
		return "";
	}
	
	memcpy(mac, OidData-> Data, 6);
	//sprintf(strTmp, "[MAC Address]: %02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	//Simple_Output_Packets_List_Without_Increment(strTmp);
	sprintf(strTmp, "%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	return strTmp;
}

void PSFilter::getAdapterIndice()
{
	char strTmp[1024];
    PIP_INTERFACE_INFO      pInterfaceInfo;
    PIP_ADAPTER_INDEX_MAP   pIndexMap;
	PBYTE   m_pBuffer = NULL;
	ULONG   m_ulSize;
	DWORD   m_dwResult;

    GetInterfaceInfo((PIP_INTERFACE_INFO) m_pBuffer, &m_ulSize);
	
    m_pBuffer = new BYTE[m_ulSize];
    if (NULL != m_pBuffer)
    {
        m_dwResult = GetInterfaceInfo((PIP_INTERFACE_INFO) m_pBuffer, &m_ulSize);
        if (m_dwResult == NO_ERROR)
        {
            pInterfaceInfo = (PIP_INTERFACE_INFO) m_pBuffer;
			
            for (int x = 0; x < pInterfaceInfo->NumAdapters; x++)
            {
                pIndexMap = (PIP_ADAPTER_INDEX_MAP) &(pInterfaceInfo->Adapter[x]);
				
                //sprintf(strTmp, "[Adapter index]: %lu  [Adapter name]: %S", pIndexMap->Index, pIndexMap->Name);
                //Simple_Output_Packets_List_Without_Increment(strTmp);
				m_niIndice.push_back(pIndexMap->Index);
				CString strTemp = pIndexMap->Name;
				m_nstrAdapterNames.push_back(strTemp);
            }
        }
        else
        {
            sprintf(strTmp, "GetInterfaceInfo() failed.  Result = %lu", m_dwResult);
            Simple_Output_Packets_List_Without_Increment(strTmp);
        }
		
        delete [] m_pBuffer;
    }
}

BOOL PSFilter::searchAdapterIndexAndName(PSNIC *pNIC)
{
	if (m_niIndice.size() != m_nstrAdapterNames.size())
	{
		MyMessageBox_Error("searchAdapterIndexAndName");
		return FALSE;
	}
	for (int i = 0; i < m_nstrAdapterNames.size(); i ++)
	{
		if (isIdenticalNICName(m_nstrAdapterNames[i], pNIC->winpcap_name))
		{
			pNIC->iphlp_name = m_nstrAdapterNames[i];
			pNIC->iphlp_index = m_niIndice[i];
			return TRUE;
		}
	}
	MyMessageBox_Error("searchAdapterIndexAndName");
	return FALSE;
}

BOOL PSFilter::isIdenticalNICName(CString strNICName1, CString strNICName2)
{
	int iStart1, iEnd1, iStart2, iEnd2;
	iStart1 = strNICName1.Find("{", 0);
	iEnd1 = strNICName1.Find("}", iStart1);
	iStart2 = strNICName2.Find("{", 0);
	iEnd2 = strNICName2.Find("}", iStart2);

	if (iStart1 == -1 || iEnd1 == -1 || iStart2 == -1 || iEnd2 == -1)
	{
		MyMessageBox_Error("isIdenticalNICName");
		return FALSE;
	}
	else
	{
		CString strNICID1 = strNICName1.Mid(iStart1 - 1, iEnd1);
		CString strNICID2 = strNICName2.Mid(iStart2 - 1, iEnd2);
		if (strNICID1 == strNICID2)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

BOOL PSFilter::listIPInfos()
{
    PMIB_IPADDRTABLE    pAddrTable;
    PMIB_IPADDRROW      pAddrRow;
    in_addr             ia;
	PBYTE   m_pBuffer = NULL;
    ULONG   m_ulSize;
	DWORD   m_dwResult;
	CString strIP;
	CString strSubnet;
	CString strBroadcast;

	if (m_nNICs.size() == 0)
	{
		return TRUE;
	}

    GetIpAddrTable((PMIB_IPADDRTABLE) m_pBuffer, &m_ulSize, TRUE);
	
    m_pBuffer = new BYTE[m_ulSize];
    if (NULL != m_pBuffer)
    {
        m_dwResult = GetIpAddrTable((PMIB_IPADDRTABLE) m_pBuffer, &m_ulSize, TRUE);
        if (m_dwResult == NO_ERROR)
        {
            pAddrTable = (PMIB_IPADDRTABLE) m_pBuffer;
			
            for (int x = 0; x < pAddrTable->dwNumEntries; x++)
            {
                pAddrRow = (PMIB_IPADDRROW) &(pAddrTable->table[x]);
                /*
                ia.S_un.S_addr = pAddrRow->dwAddr;
                m_strText.Format("IP address: %s\r\n", inet_ntoa(ia));
                m_strText.Format("Interface index: %lu\r\n", pAddrRow->dwIndex);
                ia.S_un.S_addr = pAddrRow->dwMask;
                m_strText.Format("Subnet mask: %s\r\n", inet_ntoa(ia));
                ia.S_un.S_addr = pAddrRow->dwBCastAddr;
                m_strText.Format("Broadcast address: %s\r\n", inet_ntoa(ia));
				*/
				ia.S_un.S_addr = pAddrRow->dwAddr;
                strIP.Format("%s", inet_ntoa(ia));
                ia.S_un.S_addr = pAddrRow->dwMask;
                strSubnet.Format("%s", inet_ntoa(ia));
                ia.S_un.S_addr = pAddrRow->dwBCastAddr;
                strBroadcast.Format("%s", inet_ntoa(ia));

				for (int i = 0; i < m_nNICs.size(); i ++)
				{
					if (m_nNICs[i]->iphlp_index == pAddrRow->dwIndex)
					{
						m_nNICs[i]->ip = strIP;
						m_nNICs[i]->subnet = strSubnet;
						m_nNICs[i]->broadcast = strBroadcast;
						break;
					}
				}

            }

			for (int i = 0; i < m_nNICs.size(); i ++)
			{
				if (m_nNICs[i]->ip == "")
				{
					MyMessageBox_Error("listIPInfos");
					delete []m_pBuffer;
					return FALSE;
				}
			}
        }
        else
        {
            MyMessageBox_Error("listIPInfos");
        }
		
        delete []m_pBuffer;
    }
	
    return TRUE;
}


BOOL PSFilter::listNICs(BOOL bDisplay)
{
	m_nNICs.clear();
	char strTmp[1024];

	pcap_if_t *npAdapters; //适配器列表
    pcap_if_t *pAdapter;
    char strErrorBuffer[PCAP_ERRBUF_SIZE]; //错误信息缓冲区
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &npAdapters, strErrorBuffer) == -1)
    {
		//检索机器连接的所有网络适配器
        sprintf(strTmp, "Error in pcap_findalldevs_ex function: %s\n", strErrorBuffer);
		Simple_Output_Packets_List_Without_Increment(strTmp);
    }
    if (npAdapters == NULL)
    {
		//不存在任何适配器
        sprintf(strTmp, "\nNo adapters found! Make sure WinPcap is installed.\n");
		Simple_Output_Packets_List_Without_Increment(strTmp);
        return FALSE;
    }
    int iCntAdapters = 0;
	getAdapterIndice();
    for (pAdapter = npAdapters; pAdapter != NULL; pAdapter = pAdapter->next)
    {
		//遍历输入适配器信息(名称和描述信息)
		PSNIC *pNIC = new PSNIC(iCntAdapters ++, pAdapter->name, pAdapter->description);
		searchAdapterIndexAndName(pNIC);
		m_nNICs.push_back(pNIC);
		//listIPs(pAdapter);
		pNIC->mac = getMacByWinPcapName(pNIC->winpcap_name);
    }
	listIPInfos();

	if (bDisplay)
	{
		for (int i = 0; i < m_nNICs.size(); i ++)
		{
			sprintf(strTmp, "[NIC WinPcap Index]: %d   [NIC WinPcap Name]: %s  [NIC IPHelper Index]: %d   [NIC IPHelper Name]: %s",
				m_nNICs[i]->winpcap_index, m_nNICs[i]->winpcap_name, m_nNICs[i]->iphlp_index, m_nNICs[i]->iphlp_name);
			Simple_Output_Packets_List_Without_Increment(strTmp);
			sprintf(strTmp, "[NIC Description]: %s  [NIC Mac Address]: %s  [NIC IP Address]: %s",
				m_nNICs[i]->desc, m_nNICs[i]->mac, m_nNICs[i]->ip);
			Simple_Output_Packets_List(strTmp);
		}
	}
    //printf("\n");
    pcap_freealldevs(npAdapters); //释放适配器列表
	return FALSE;
}


int PSFilter::captureNIC(int iSrcNICNo, int iDestNICNo)
{
	char strTmp[1024];

	pcap_if_t *npAdapters; //适配器列表
    pcap_if_t *pAdapter;
	pcap_t *hAdapter; //适配器句柄
    struct pcap_pkthdr *packetHeader;
    const u_char *packetData;
    char strErrorBuffer[PCAP_ERRBUF_SIZE]; //错误信息缓冲区
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &npAdapters, strErrorBuffer) == -1)
    {
		//检索机器连接的所有网络适配器
        sprintf(strTmp, "Error in pcap_findalldevs_ex function: %s\n", strErrorBuffer);
		Simple_Output_Packets_List_Without_Increment(strTmp);
    }
    if (npAdapters == NULL)
    {
		//不存在任何适配器
        sprintf(strTmp, "\nNo adapters found! Make sure WinPcap is installed.\n");
		Simple_Output_Packets_List_Without_Increment(strTmp);
    }
    int iCntAdapters = 0;
    for (pAdapter = npAdapters; pAdapter != NULL; pAdapter = pAdapter->next)
    {
		//遍历输入适配器信息(名称和描述信息)
		iCntAdapters ++;
		/*
        sprintf(strTmp, "\n%d.%s ", iCntAdapters ++, pAdapter->name);
		Simple_Output_Console(strTmp);
        sprintf(strTmp, "-- %s\n", pAdapter->description);
		Simple_Output_Console_Without_Increment(strTmp);
		*/
    }
    //printf("\n");
    //pcap_freealldevs(npAdapters); //释放适配器列表


    //捕获数据包
    if (iSrcNICNo < 0 || iSrcNICNo >= iCntAdapters)
    {
        sprintf(strTmp, "\nAdapter number out of range.\n");
		Simple_Output_Packets_List_Without_Increment(strTmp);
        // 释放适配器列表
        pcap_freealldevs(npAdapters);
        return -1;
    }
    pAdapter = npAdapters;
    for (int i = 0; i < iSrcNICNo; i ++)
		pAdapter = pAdapter->next;
    // 打开指定适配器
    hAdapter = pcap_open(pAdapter->name, // name of the adapter
		65536,         // portion of the packet to capture
		// 65536 guarantees that the whole 
		// packet will be captured
		PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
		1000,             // read timeout - 1 millisecond
		NULL,          // authentication on the remote machine
		strErrorBuffer    // error buffer
		);
    if (hAdapter == NULL)
    {
		//指定适配器打开失败
        sprintf(strTmp, "\nUnable to open the adapter: %s\n", pAdapter->name);
		Simple_Output_Packets_List_Without_Increment(strTmp);
        // 释放适配器列表
        pcap_freealldevs(npAdapters);
        return -1;
    }
    sprintf(strTmp, "\nCapture session started on adapter %s\n", pAdapter->name);
	Simple_Output_Packets_List_Without_Increment(strTmp);

	if (iDestNICNo != -1)
	{
		pAdapter = npAdapters;
		for (int i = 0; i < iDestNICNo; i ++)
			pAdapter = pAdapter->next;
		// 打开指定适配器
		m_hDestNIC = pcap_open(pAdapter->name, // name of the adapter
			65536,         // portion of the packet to capture
			// 65536 guarantees that the whole 
			// packet will be captured
			PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
			1000,             // read timeout - 1 millisecond
			NULL,          // authentication on the remote machine
			strErrorBuffer    // error buffer
			);
		if (hAdapter == NULL)
		{
			//指定适配器打开失败
			sprintf(strTmp, "\nUnable to open the adapter: %s\n", pAdapter->name);
			Simple_Output_Packets_List_Without_Increment(strTmp);
			// 释放适配器列表
			pcap_freealldevs(npAdapters);
			return -1;
		}
		sprintf(strTmp, "\nForwarding session started on adapter %s\n", pAdapter->name);
		Simple_Output_Packets_List_Without_Increment(strTmp);
	}
	else
	{
		m_hDestNIC = NULL;
	}

    pcap_freealldevs(npAdapters);//释放适配器列表


    // 开始捕获数据包
    int iCntPackets;
    while ((iCntPackets = pcap_next_ex(hAdapter, &packetHeader, &packetData)) >= 0 && m_bStop == FALSE)
    {
        // timeout elapsed if we reach this point
        if (iCntPackets == 0)
			continue;
        //打印捕获数据包的信息
		CString strDesc;
		CString strProtocolType = protocol2String2(parsePacket((BYTE*) packetData, packetHeader->len, strDesc));

        sprintf(strTmp, "[Packet Type]: %s  [Frame Length]:%4d   %s\n", strProtocolType, packetHeader->len, strDesc);
		Simple_Output_Packets_List(strTmp);
		/*
		for (int j = 0; j < 1; j ++)
		{
			Output_Dump_EditBox(strTmp);
			Output_Text_EditBox(strTmp);
		}
		*/

		if (m_hDestNIC != NULL)
		{
			forwardPacket(m_hDestNIC, (BYTE*) packetData, packetHeader->len);
		}

		
    }
    // if we get here, there was an error reading the packets
    if (iCntPackets == -1)
    {
        sprintf(strTmp, "Error reading the packets: %s\n", pcap_geterr( hAdapter));
		Simple_Output_Packets_List_Without_Increment(strTmp);
        return -1;
    }

	return 0;
}

int PSFilter::forwardPacket(pcap_t *hAdapter, BYTE *byPacketData, int iSize)
{
	if (pcap_sendpacket(hAdapter, // the adapter handle
						byPacketData, // the packet
						iSize // the length of the packet
						) != 0)
    {
		char strTmp[1024];
        sprintf(strTmp, "\nError sending the packet: %s\n", pcap_geterr(hAdapter));
		Simple_Output_Packets_List_Without_Increment(strTmp);
        return -1;
    }
	return 0;
}

int PSFilter::parsePacket(BYTE *byPacketData, int iSize, CString &strDesc)
{
	strDesc = "";
	//Get Frame type
	EthernetHeader *ethernetHeader = (EthernetHeader*) byPacketData;
	
	if(ntohs(ethernetHeader->type) == 0x0800) //IP
	{
		
	}
	else if(ntohs(ethernetHeader->type)==0x0806)//arp
	{
		return PACKET_ARP;
	}
	else if (ntohs(ethernetHeader->type)==0xdd86)
	{
		//ipv6
		return PACKET_IPV6;
	}
	else
	{
		return PACKET_UNKNOWN;
	}

	//Handle ARP/RARP frame.......
	/*
	if(ntohs(eh->type) == 0x0806)
	{
		arp_header *arph = (arp_header*)(pkt_data + ETHER_LENGTH);
		
		//Information
		if(ntohs(arph->opcode)==0x0001)
		{
			
		}
		
		if(ntohs(arph->opcode)==0x0002)
		{
			
		}
		
		if(ntohs(arph->opcode)==0x0003)
		{
			
		}
		
		if(ntohs(arph->opcode)==0x0002)
		{
			
		}
		
		return TRUE;	
	}
	*/
	
	//Get IP Header...
	IPHeader *ipHeader = (IPHeader*)(byPacketData + ETHER_HEADER_LENGTH);

	int iSrcIP = ipHeader->ipSource;
	int iDestIP = ipHeader->ipDestination;
	char strSrcIP[20] = "                   ";
	char strDestIP[20] = "                   ";
	//sprintf(strTmp, "[Frame Type]: %s, [Frame Length]: %d, %s\n", strProtocolType, packetHeader->len, strDesc);
	sprintf(strSrcIP, "%u.%u.%u.%u", iSrcIP & 0xff, iSrcIP >> 8 & 0xff, iSrcIP >> 16 & 0xff, iSrcIP >> 24 & 0xff);
	sprintf(strDestIP, "%u.%u.%u.%u", iDestIP & 0xff, iDestIP >> 8 & 0xff, iDestIP >> 16 & 0xff, iDestIP >> 24 & 0xff);
	expandString(strSrcIP, 16);
	expandString(strDestIP, 16);
	strDesc += "[Src IP]: ";
	strDesc += strSrcIP;
	strDesc += " [Dest IP]: ";
	strDesc += strDestIP;

	//Get the length of IP Header
	int iIPHeaderLength = (ipHeader->iphVerLen & 0xf) << 2;
	//int iIPDataLength = ipHeader->ipLength - iIPHeaderLength;
	int iIPDataLength = iSize - ETHER_HEADER_LENGTH - iIPHeaderLength;
	
	switch(ipHeader->ipProtocol)
	{
	case 1: //ICMP
		{
			//icmph = (icmp_header*)(byPacketData + ETHER_LENGTH + ip_hlen);
			return PACKET_ICMP;
		}
		break;
		
	case 2: //IGMP
		{
			//igmph = (igmp_header*)(byPacketData + ETHER_LENGTH + ip_hlen);
			return PACKET_IGMP;
		}
		break;
		
	case 6: //TCP
		{
			TCPHeader *tcpHeader = (TCPHeader*) (byPacketData + ETHER_HEADER_LENGTH + iIPHeaderLength);

			int iSrcPort = tcpHeader->sourcePort;
			int iDestPort = tcpHeader->destinationPort;
			BYTE *pData = (BYTE*) (tcpHeader + TCP_HEADER_LENGTH);
			int cbData = iIPDataLength - TCP_HEADER_LENGTH;
			char strSrcPort[10] = "         ";
			char strDestPort[10] = "         ";
			char strCbData[10] = "         ";
			sprintf(strSrcPort, "%d", iSrcPort);
			sprintf(strDestPort, "%d", iDestPort);
			sprintf(strCbData, "%5d", cbData);
			expandString(strSrcPort, 6);
			expandString(strDestPort, 6);
			//expandString(strDestPort, 5);
			strDesc += " [Src Port]: ";
			strDesc += strSrcPort;
			strDesc += "   [Dest Port]: ";
			strDesc += strDestPort;
			strDesc += "[Data Length]: ";
			strDesc += strCbData;

			extractPacket(pData, cbData);

			return PACKET_TCP;
		}
		break;
		
	case 17: //UDP
		{
			UDPHeader *udpHeader = (UDPHeader*) (byPacketData + ETHER_HEADER_LENGTH + iIPHeaderLength);

			int iSrcPort = udpHeader->sourcePort;
			int iDestPort = udpHeader->destinationPort;
			BYTE *pData = (BYTE*) (udpHeader + UDP_HEADER_LENGTH);
			int cbData = iIPDataLength - UDP_HEADER_LENGTH;
			char strSrcPort[10] = "         ";
			char strDestPort[10] = "         ";
			char strCbData[10] = "         ";
			sprintf(strSrcPort, "%d", iSrcPort);
			sprintf(strDestPort, "%d", iDestPort);
			sprintf(strCbData, "%5d", cbData);
			expandString(strSrcPort, 6);
			expandString(strDestPort, 6);
			//expandString(strDestPort, 5);
			strDesc += " [Src Port]: ";
			strDesc += strSrcPort;
			strDesc += "   [Dest Port]: ";
			strDesc += strDestPort;
			strDesc += "[Data Length]: ";
			strDesc += strCbData;

			extractPacket(pData, cbData);

			return PACKET_UDP;
		}
	break;
	default: //IP
		{
			return PACKET_IPV4;
		}
	break;
	}
}

void PSFilter::extractPacket(BYTE *pData, int cbData)
{
	if (cbData < 150)
	{
		return;
	}

	BYTE *pHead = NULL;
	BYTE *pRear = NULL;
	for (int i = 0; i < cbData; i ++)
	{
		if (pData[i] == GETPC1 || pData[i] == GETPC2)
		{
			//if (pRear - pData < 50)
			//{
			//	continue;
			//}
			if (cbData < 400)
			{
				pHead = pData;
				pRear = pData + cbData;
			}
			else
			{
				pHead = pData + i - 50;
				pRear = pData + i + 350;
			
				if (pHead < pData)
				{
					pRear += (pData - pHead);
					pHead += (pData - pHead);
				}
				if (pRear > pData + cbData)
				{
					pHead -= (pRear - pData - cbData);
					pRear -= (pRear - pData - cbData);
				}
			}

			int cbShellcode = pRear - pHead;
			int iGetPC = pData + i - pHead;
			BYTE *pShellcode = (BYTE*) malloc(cbShellcode * sizeof(BYTE));
			memcpy(pShellcode, pHead, cbShellcode);
			PSShellcode *shellcode = new PSShellcode(m_iPacketNo, m_iShellcodeNo, pShellcode, cbShellcode, iGetPC);
			Output_Shellcode(shellcode);

			char strTmp[1024];
			sprintf(strTmp, "[Packet No.]:%5d  [Shellcode Length]:%4d  [GetPC Offset]:%4d\n", m_iPacketNo, cbShellcode, iGetPC);
			Simple_Output_GetPC_List(strTmp);
			
			i = pRear - pData;
		}
	}
}