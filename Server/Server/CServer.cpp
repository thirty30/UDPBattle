#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CServer)

CServer::CServer()
{
	this->m_IsRun = false;
	this->m_mapSID2Session.clear();
	this->m_fLastFrameTime = 0;
}

CServer::~CServer()
{

}

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

void CServer::OnConnected(sockaddr_in& a_rClient)
{
	u64 nSID = CalcSessionID(a_rClient);
	CSession* pSession = this->FindSession(nSID);
	if (pSession != NULL)
	{
		return;
	}
	this->AddSession(a_rClient);
	cout << "new session: " << nSID << endl;
}

void CServer::OnDisconnected(sockaddr_in& a_rClient)
{
	u64 nSID = CalcSessionID(a_rClient);
	CBattle::GetSingleton().DeletePlayer(nSID);
	this->DeleteSession(nSID);
}

void CServer::OnReceived(sockaddr_in& a_rClient, tcchar* a_pData, n32 a_nSize)
{
	CSession* pSession = this->FindSession(a_rClient);
	if (pSession == NULL)
	{
		return;
	}
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
	(this->*m_HandlerTable[uMsgID])(uMsgID, pSession->m_nSessionID, pData, nDataSize);
}

void CServer::SendToClient(u32 a_uMsgID, u64 a_nSID, const PMessageBase& a_Msg)
{
	CSession* pSession = this->FindSession(a_nSID);
	if (pSession == NULL)
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
	sendto(this->m_nListenFD, m_pSendBuffer, sHeader.GetMsgLength(), 0, (struct sockaddr*)&pSession->m_pClient, sizeof(pSession->m_pClient));
}

void CServer::SendToClient(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pData, u32 a_uLen)
{
	CSession* pSession = this->FindSession(a_nSID);
	if (pSession == NULL)
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

	sendto(this->m_nListenFD, m_pSendBuffer, sHeader.GetMsgLength(), 0, (struct sockaddr*)&pSession->m_pClient, sizeof(pSession->m_pClient));
}

tbool CServer::Init()
{
	srand(TGetTimeStamp());

	if (InitNet() == false)
	{
		cout << "Init Net Failed..." << endl;
		return false;
	}

	if (this->m_Battle.Init() == false)
	{
		cout << "Init Battle Failed..." << endl;
		return false;
	}

	cout << "Server Started..." <<endl;
	return true;
}

tbool CServer::InitNet()
{
	this->m_pReceiveBuffer = new tcchar[SERVER_RECEIVE_BUFFER_SIZE];
	this->m_pSendBuffer = new tcchar[SERVER_SEND_BUFFER_SIZE];
	m_SendHeap.AllocHeap(MAX_SEND_HEAP_LENGTH);
	RegisterMessageHeap(&m_SendHeap);

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

	sockaddr_in receAddr;
	receAddr.sin_family = AF_INET;
	receAddr.sin_port = htons(LISTEN_PORT);
	receAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->m_nListenFD, (SOCKADDR*)&receAddr, sizeof(receAddr)) == SOCKET_ERROR)
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

	n32 nLen = recvfrom(this->m_nListenFD, this->m_pReceiveBuffer, SERVER_RECEIVE_BUFFER_SIZE, 0, (struct sockaddr*)&client, &nClientLen);
	if (nLen > 0)
	{
		this->OnConnected(client);
		this->OnReceived(client, this->m_pReceiveBuffer, nLen);
	}
	else
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return;
		}

		if (WSAGetLastError() == WSAECONNRESET)
		{
			this->OnDisconnected(client);
		}

		TMemzero(this->m_pReceiveBuffer, SERVER_RECEIVE_BUFFER_SIZE);
	}
}

void CServer::Run()
{
	m_IsRun = true;
	while (m_IsRun == true)
	{
		f32 fNowTime = (f32)m_Counter.GetCurrentFramesTime();
		f32 fDeltaTime = fNowTime - this->m_fLastFrameTime;
		f32 fLimitTime = 1.0f / 60;
		if (fDeltaTime < fLimitTime)
		{
			continue;
		}
		
		this->m_fLastFrameTime = fNowTime;
		this->LoopNet();
		this->m_Battle.Update(fNowTime, fDeltaTime);
	}
}

void CServer::Clear()
{
	delete m_pSendBuffer;

	hash_map<u64, CSession*>::const_iterator iter = this->m_mapSID2Session.begin();
	for (; iter != this->m_mapSID2Session.end(); iter++)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
		}
	}
	this->m_mapSID2Session.clear();

	UnRegisterMessageHeap(&m_SendHeap);
}

CSession* CServer::FindSession(u64 a_nSessionID)
{
	hash_map<u64, CSession*>::const_iterator iter = this->m_mapSID2Session.find(a_nSessionID);
	if (iter == this->m_mapSID2Session.end())
	{
		return NULL;
	}
	return iter->second;
}

CSession* CServer::FindSession(sockaddr_in& a_rClient)
{
	u64 nSessionID = CalcSessionID(a_rClient);
	hash_map<u64, CSession*>::const_iterator iter = this->m_mapSID2Session.find(nSessionID);
	if (iter == this->m_mapSID2Session.end())
	{
		return NULL;
	}
	return iter->second;
}

void CServer::AddSession(sockaddr_in& a_rClient)
{
	CSession* pSession = new CSession(a_rClient);
	this->m_mapSID2Session[pSession->m_nSessionID] = pSession;
}

void CServer::DeleteSession(u64 a_nSessionID)
{
	CSession* pSession = this->FindSession(a_nSessionID);
	if (pSession == NULL)
	{
		return;
	}
	delete pSession;
	this->m_mapSID2Session.erase(a_nSessionID);
}
