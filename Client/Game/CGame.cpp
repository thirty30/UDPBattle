#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CGame)
	
CGame::CGame()
{
	this->m_nScreenWidth = 1600;
	this->m_nScreenHigh = 900;
	this->m_strWindowName = "pExample";
	this->m_pResManager = NULL;
	this->m_pScene = NULL;
	this->m_eGameStatus = E_GAME_STATUS_INIT;
}

CGame::~CGame()
{
	this->ClearGame();
}

tbool CGame::InitGame()
{
	TMuffin_RegisterKeyCallback(ControlKeyEvent);
	TMuffin_RegisterMouseCallback(ControlMouseEvent);
	TMuffin_RegisterCursorCallback(ControlCursorEvent);
	TMuffin_RegisterScrollCallback(ControlScrollEvent);
	TMuffin_RegisterGameLogicCallBack(CGame::GameLogicCallBack);
	
	if (TMuffin_Initialize(this->m_nScreenWidth, this->m_nScreenHigh, this->m_strWindowName.c_str()) == false)
	{
		return false;
	}

	if (this->InitNet() == false)
	{
		return false;
	}

	this->m_pResManager = new CResourceManager();
	if (this->m_pResManager->Init() == false)
	{
		return false;
	}
	
	this->m_pScene = new CScene();
	if (m_pScene->Init() == false)
	{
		return false;
	}

	return true;
}

void CGame::ClearGame()
{
	//release game data
	if (this->m_pResManager != NULL)
	{
		delete this->m_pResManager;
		this->m_pResManager = NULL;
	}
	if (this->m_pScene != NULL)
	{
		this->m_pScene->Clear();
		delete this->m_pScene;
		this->m_pScene = NULL;
	}

	UnRegisterMessageHeap(&m_SendHeap);

	//release engine
	TMuffin_Clear();
}

void CGame::LoopGame()
{
	TMuffin_Loop();
}

tbool CGame::InitNet()
{
	this->m_pReceiveBuffer = new tcchar[RECEIVE_BUFFER_SIZE];
	this->m_pSendBuffer = new tcchar[SEND_BUFFER_SIZE];
	m_SendHeap.AllocHeap(MAX_SEND_HEAP_LENGTH);
	RegisterMessageHeap(&m_SendHeap);

	this->m_nSocketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->m_nSocketFD == SOCKET_ERROR)
	{
		return false;
	}

	TMemzero((tcchar*)&this->m_sockAddr, sizeof(this->m_sockAddr));
	this->m_sockAddr.sin_family = AF_INET;
	this->m_sockAddr.sin_port = htons(SERVER_PORT);
	this->m_sockAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	unsigned long ub = 1;
	if (ioctlsocket(this->m_nSocketFD, FIONBIO, (unsigned long*)&ub) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

void CGame::LoopNet()
{
	sockaddr_in server;
	n32 nServerLen = sizeof(server);
	n32 nLen = recvfrom(this->m_nSocketFD, this->m_pReceiveBuffer, RECEIVE_BUFFER_SIZE, 0, (struct sockaddr*)&server, &nServerLen);
	if (nLen > 0)
	{
		this->OnReceived(this->m_pReceiveBuffer, nLen);
	}
	else if (nLen == 0)
	{

	}
	else
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return;
		}
		TMemzero(this->m_pReceiveBuffer, RECEIVE_BUFFER_SIZE);
	}
}

void CGame::OnReceived(tcchar* a_pData, n32 a_nSize)
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
	(this->*m_HandlerTable[uMsgID])(uMsgID, pData, nDataSize);
}

void CGame::SendToServer(u32 a_uMsgID, const PMessageBase& a_Msg)
{
	MessageHeader sHeader;
	n32 nHeaderSize = sHeader.GetLength();
	n32 nMsgLen = a_Msg.Serialize(m_pSendBuffer + nHeaderSize, SEND_BUFFER_SIZE - nHeaderSize);
	sHeader.SetMsgID(a_uMsgID);
	sHeader.SetMsgLength(nHeaderSize + nMsgLen);
	sHeader.SetCompress(0);
	sHeader.Serialize(m_pSendBuffer, nHeaderSize);
	sendto(this->m_nSocketFD, m_pSendBuffer, sHeader.GetMsgLength(), 0, (struct sockaddr*)&this->m_sockAddr, sizeof(this->m_sockAddr));
}

void CGame::SendToServer(u32 a_uMsgID, const tcchar* a_pData, u32 a_uLen)
{
	MessageHeader sHeader;
	n32 nHeaderSize = sHeader.GetLength();
	sHeader.SetMsgID(a_uMsgID);
	sHeader.SetMsgLength(nHeaderSize + a_uLen);
	sHeader.SetCompress(0);
	sHeader.Serialize(m_pSendBuffer, nHeaderSize);
	TMemcpy(m_pSendBuffer + nHeaderSize, SEND_BUFFER_SIZE - nHeaderSize, a_pData, a_uLen);
	sendto(this->m_nSocketFD, m_pSendBuffer, sHeader.GetMsgLength(), 0, (struct sockaddr*)&this->m_sockAddr, sizeof(this->m_sockAddr));
}

void CGame::SetScreenSize(n32 a_nWidth, n32 a_nHigh)
{
	this->m_nScreenWidth = a_nWidth;
	this->m_nScreenHigh = a_nHigh;
}

void CGame::GameLogicLoop()
{
	if (this->m_eGameStatus == E_GAME_STATUS_INIT)
	{
		this->m_eGameStatus = E_GAME_STATUS_LOAD_SCENE_START;
	}
	else if (this->m_eGameStatus == E_GAME_STATUS_LOAD_SCENE_START)
	{
		this->m_pScene->LoadScene();
		this->m_eGameStatus = E_GAME_STATUS_LOAD_SCENE_FINISH;
	}
	else if (this->m_eGameStatus == E_GAME_STATUS_LOAD_SCENE_FINISH)
	{
		this->m_pScene->Loop();
	}
	this->InitNet();
}


