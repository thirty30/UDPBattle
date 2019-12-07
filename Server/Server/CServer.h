#pragma once

class CServer : public CSingleton<CServer>
{
private:
	TMessageSendHeap m_SendHeap;	//send message buffer
	tbool m_IsRun;
	tcchar* m_pSendBuffer;
	hash_map<socketfd, CSession*> m_mapFd2Session;
	socketfd m_nListenFD;
	tcchar* m_pReceiveBuffer;


public:
	CServer() : m_IsRun(false)
	{
		this->m_pReceiveBuffer = new tcchar[SERVER_RECEIVE_BUFFER_SIZE];
	}

	~CServer()
	{

	}

public:
	//if got a completed package return the length, otherwise return -1
	static n32 OnAnalysisPackage(tcchar* a_pData, n32 a_nSize);

public:

	virtual void OnConnected(socketfd a_nFd);
	virtual void OnDisconnected(socketfd a_nFd);
	virtual void OnReceived(socketfd a_nFd, tcchar* a_pData, n32 a_nSize);
	virtual void OnSendOver(socketfd a_nFd);
	virtual void OnException(socketfd a_nFd, n16 a_event);

public:
	void SendToClient(u32 a_uMsgID, socketfd a_nFd, const PMessageBase& a_Msg);
	void SendToClient(u32 a_uMsgID, socketfd a_nFd, const tcchar* a_pData, u32 a_uLen);

	CSession* GetSession(socketfd a_nFd);

private:
#include "./MessageHandler.h"

private:
	void KickConnection(socketfd a_nFd);

public:

	tbool Init();
	tbool InitNet();
	void LoopNet();
	void Run();
	void Clear();
};
