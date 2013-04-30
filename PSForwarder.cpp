#include "StdAfx.h"
#include "PSForwarder.h"
#include "PSFilter.h"

//#include <windows.h>
#include <Iphlpapi.h>
#include <winsock2.h>

PSSimpleNIC::PSSimpleNIC(CString strIP)
{
	mac = retrieveMacFromIP(ip);
}

CString PSSimpleNIC::retrieveMacFromIP(CString strIP)
{
	unsigned char arDestMac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	ULONG ulLen = 6;
	if (::SendARP(::inet_addr(strIP), 0, (ULONG*) arDestMac, &ulLen) == NO_ERROR)
	{
		// 打印出结果
		u_char *p = arDestMac;
		CString strMac;
		strMac.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"), p[0], p[1], p[2], p[3], p[4], p[5]);
		return strMac;
		//printf("pEtherh->shost: %02X-%02X-%02X-%02X-%02X-%02X \n", p[0], p[1], p[2], p[3], p[4], p[5]);
	}
	else
	{
		MyMessageBox_Error(_T("retrieveMacFromIP"));
		return _T("");
	}
}

PSForwarder::PSForwarder(CString strRelayIP, vector<PSNIC*> npNICs)
{
	pRelayNIC = new PSSimpleNIC(strRelayIP);
	m_npNICs = npNICs;
}

PSForwarder::~PSForwarder()
{
	for (int i = 0; i < m_npNICs.size(); i ++)
	{
		delete m_npNICs[i];
	}
	m_npNICs.clear();
}

BOOL PSForwarder::checkIP(CString strIP)
{
	char *str = strIP.GetBuffer(0);
	
    int segs = 0;   /* Segment count. */
    int chcnt = 0;  /* Character count within segment. */
    int accum = 0;  /* Accumulator for segment. */
	
    /* Catch NULL pointer. */
	
    if (str == NULL)
        return 0;
	
    /* Process every character in string. */
	
    while (*str != '\0') {
        /* Segment changeover. */
		
        if (*str == '.') {
            /* Must have some digits in segment. */
			
            if (chcnt == 0)
                return 0;
			
            /* Limit number of segments. */
			
            if (++segs == 4)
                return 0;
			
            /* Reset segment values and restart loop. */
			
            chcnt = accum = 0;
            str++;
            continue;
        }
		
		
        /* Check numeric. */
		
        if ((*str < '0') || (*str > '9'))
            return 0;
		
        /* Accumulate and check segment. */
		
        if ((accum = accum * 10 + *str - '0') > 255)
            return 0;
		
        /* Advance other segment specific stuff and continue loop. */
		
        chcnt++;
        str++;
    }
	
    /* Check enough segments and enough characters in last segment. */
	
    if (segs != 3)
        return 0;
	
    if (chcnt == 0)
        return 0;
	
    /* Address okay. */
	
    return 1;
}

BOOL PSForwarder::FolderExist(CString strPath)
{
	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;
	}
	FindClose(hFind);
	return rValue;
}

void PSForwarder::initDataDir()
{
	CString cstrDir;
	TCHAR cBuffer[260];
	GetCurrentDirectory(MAX_PATH, cBuffer);
	CString cstrPath(cBuffer);
	if (FolderExist(cstrPath + _T("\\data")))
	{
		cstrDir = cstrPath;
	}
	else
	{
		int nCount = cstrPath.ReverseFind(_T('\\'));
		cstrPath.Delete(nCount, cstrPath.GetLength() - nCount);
		
		if (FolderExist(cstrPath + _T("\\data")))
		{
			cstrDir = cstrPath;
		}
		else
		{
			MyMessageBox_Error(_T("initDataDir Error"), _T("Error"));
			return;
		}
	}
	cstrDir += _T("\\data\\");
	m_strDataDirectory = cstrDir;
}

void PSForwarder::clearSimpleNICs()
{
	for (int i = 0; i < m_npHostNICs.size(); i ++)
	{
		delete m_npHostNICs[i];
	}
	m_npHostNICs.clear();

	for (i = 0; i < m_npVMNICs.size(); i ++)
	{
		delete m_npVMNICs[i];
	}
	m_npVMNICs.clear();
}

void PSForwarder::readListFromFile()
{
	clearSimpleNICs();

	CString strTablePathName = m_strDataDirectory + _T("forward_table.txt");
	CStdioFile file;
	if (file.Open(strTablePathName, CFile::modeReadWrite) == FALSE)
	{
		MyMessageBox_Error(_T("readListFromFile"));
		return;
	}

	CString strLine;
	while (file.ReadString(strLine))
	{
		int iFirstEnd = strLine.Find(_T("<--->"));
		int iSecondStart = iFirstEnd + 5;
		iFirstEnd --;
		while (iFirstEnd >= 1 && strLine[iFirstEnd] == _T(' '))
		{
			iFirstEnd --;
		}
		while (iSecondStart < strLine.GetLength() - 1 && strLine[iSecondStart] == _T(' '))
		{
			iSecondStart ++;
		}

		CString strHostIP = strLine.Left(iFirstEnd + 1);
		CString strVMIP = strLine.Right(strLine.GetLength() - iSecondStart);
		if (!checkIP(strHostIP) || !checkIP(strVMIP))
		{
			MyMessageBox_Error(_T("readListFromFile"));
			return;
		}
		else
		{
			PSSimpleNIC *pHostNIC = new PSSimpleNIC(strHostIP);
			PSSimpleNIC *pVMNIC = new PSSimpleNIC(strVMIP);
			m_npHostNICs.push_back(pHostNIC);
			m_npVMNICs.push_back(pVMNIC);
		}
	}

	file.Close();
}
