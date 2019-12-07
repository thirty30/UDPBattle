#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CServer)

n32 CServer::OnAnalysisPackage(tcchar* a_pData, n32 a_nSize)
{
	MessageHeader sHeader;
	n32 nHeaderSize = (n32)sHeader.GetLength();
	if (a_nSize < nHeaderSize)
	{
		return -1;
	}

	sHeader.Deserialize(a_pData, nHeaderSize);
	n32 uMsgLength = (n32)sHeader.GetMsgLength();

	if (uMsgLength > a_nSize)
	{
		return -1;
	}
	if (uMsgLength <= 0 || uMsgLength > 2048)
	{
		return -1;
	}

	return uMsgLength;
}

void CServer::KickConnection(socketfd a_nFd)
{

}

void CServer::OnConnected(socketfd a_nFd)
{
	hash_map<socketfd, CSession*>::const_iterator iter = m_mapFd2Session.find(a_nFd);
	if (iter != m_mapFd2Session.end())
	{
		KickConnection(a_nFd);
		return;
	}
	CSession* pNewSession = new CSession(a_nFd);
	m_mapFd2Session[a_nFd] = pNewSession;
}

void CServer::OnDisconnected(socketfd a_nFd)
{
	u64 uSessionID = 0;
	hash_map<socketfd, CSession*>::const_iterator iter = m_mapFd2Session.find(a_nFd);
	if (iter == m_mapFd2Session.end())
	{
		return;
	}
	m_mapFd2Session.erase(a_nFd);
}

void CServer::OnReceived(socketfd a_nFd, tcchar* a_pData, n32 a_nSize)
{
	MessageHeader sHeader;
	n32 nHeaderSize = (n32)sHeader.GetLength();
	sHeader.Deserialize(a_pData, nHeaderSize);
	n32 uMsgLength = (n32)sHeader.GetMsgLength();
	if (uMsgLength != a_nSize)
	{
		return;
	}
	u32 uMsgID = sHeader.GetMsgID();
	const tcchar* pData = a_pData + nHeaderSize;
	n32 nDataSize = uMsgLength - nHeaderSize;
	(this->*m_HandlerTable[uMsgID])(uMsgID, a_nFd, pData, nDataSize);
}

void CServer::OnSendOver(socketfd a_nFd)
{

}

void CServer::OnException(socketfd a_nFd, n16 a_event)
{

}

void CServer::SendToClient(u32 a_uMsgID, socketfd a_nFd, const PMessageBase& a_Msg)
{
	hash_map<socketfd, CSession*>::const_iterator iter = m_mapFd2Session.find(a_nFd);
	if (iter == m_mapFd2Session.end())
	{
		return;
	}
	MessageHeader sHeader;
	n32 nHeaderSize = sHeader.GetLength();
	n32 nMsgLen = a_Msg.Serialize(m_pSendBuffer + nHeaderSize, SERVER_SEND_BUFFER_SIZE - nHeaderSize);

	sHeader.SetMsgID(a_uMsgID);
	sHeader.SetMsgLength(nHeaderSize + nMsgLen);
	sHeader.SetCompress(0);
	sHeader.Serialize(m_pSendBuffer, nHeaderSize);


}

void CServer::SendToClient(u32 a_uMsgID, socketfd a_nFd, const tcchar* a_pData, u32 a_uLen)
{
	hash_map<socketfd, CSession*>::const_iterator iter = m_mapFd2Session.find(a_nFd);
	if (iter == m_mapFd2Session.end())
	{
		return;
	}
	MessageHeader sHeader;
	n32 nHeaderSize = sHeader.GetLength();
	sHeader.SetMsgID(a_uMsgID);
	sHeader.SetMsgLength(nHeaderSize + a_uLen);
	sHeader.SetCompress(0);

	sHeader.Serialize(m_pSendBuffer, nHeaderSize);
	TMemcpy(m_pSendBuffer + nHeaderSize, SERVER_SEND_BUFFER_SIZE - nHeaderSize, a_pData, a_uLen);

}

CSession* CServer::GetSession(socketfd a_nFd)
{
	hash_map<socketfd, CSession*>::const_iterator iter = this->m_mapFd2Session.find(a_nFd);
	if (iter == this->m_mapFd2Session.end())
	{
		return NULL;
	}
	return iter->second;
}

tbool CServer::Init()
{
	m_mapFd2Session.clear();

	if (InitNet() == false)
	{
		cout << "Init Net Fail..." << endl;
		return false;
	}

	m_SendHeap.AllocHeap(MAX_SEND_HEAP_LENGTH);
	RegisterMessageHeap(&m_SendHeap);

	cout << "Server Started..." <<endl;
	return true;
}

tbool CServer::InitNet()
{
	InitMessageHandler();

	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	DWORD Res = WSAStartup(wVersion, &wsaData);
	if (Res != 0)
	{
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return false;
	}

	this->m_nListenFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->m_nListenFD == INVALID_SOCKET) 
	{
		return false;
	}

	// Step #2 Bind our socket
	SOCKADDR_IN receiverAddr;
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(LISTEN_PORT);
	receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->m_nListenFD, (SOCKADDR*)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR)
	{
		return false;
	}

	unsigned long ub = 1;
	if (ioctlsocket(this->m_nListenFD, FIONBIO, (unsigned long*)&ub) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void CServer::LoopNet()
{
	sockaddr_in client;
	n32 nClientLen = sizeof(client);

	n32 nRes = recvfrom(this->m_nListenFD, this->m_pReceiveBuffer, SERVER_RECEIVE_BUFFER_SIZE, 0, (struct sockaddr*)&client, &nClientLen);
	if (nRes == SOCKET_ERROR) 
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			return;
		}
		
		TMemzero(this->m_pReceiveBuffer, SERVER_RECEIVE_BUFFER_SIZE);
		return;
	}
}

void CServer::Run()
{
	m_IsRun = true;
	while (m_IsRun == true)
	{
		this->LoopNet();
	}
}

void CServer::Clear()
{
	delete m_pSendBuffer;

	for (hash_map<socketfd, CSession*>::const_iterator iter = m_mapFd2Session.begin(); iter != m_mapFd2Session.end(); iter++)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
		}
	}

	m_mapFd2Session.clear();
	UnRegisterMessageHeap(&m_SendHeap);
}
