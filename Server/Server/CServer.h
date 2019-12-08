#pragma once

class CServer : public CSingleton<CServer>
{
private:
	TTimeCounter m_Counter;
	f32 m_fLastFrameTime;
	TMessageSendHeap m_SendHeap;	//send message buffer
	tbool m_IsRun;
	SOCKET m_nListenFD;
	tcchar* m_pSendBuffer;
	tcchar* m_pReceiveBuffer;
	hash_map<u64, CSession*> m_mapSID2Session;
	CBattle m_Battle;

private:
#include "./MessageHandler.h"

public:
	CServer();
	~CServer();

public:
	static n32 OnAnalysisPackage(tcchar* a_pData, n32 a_nSize);

public:

	void OnConnected(sockaddr_in& a_rClient);
	void OnDisconnected(sockaddr_in& a_rClient);
	void OnReceived(sockaddr_in& a_rClient, tcchar* a_pData, n32 a_nSize);
	void SendToClient(u32 a_uMsgID, u64 a_nSID, const PMessageBase& a_Msg);
	void SendToClient(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pData, u32 a_uLen);

public:
	tbool Init();
	tbool InitNet();
	void LoopNet();
	void Run();
	void Clear();

	CSession* FindSession(u64 a_nSessionID);
	CSession* FindSession(sockaddr_in& a_rClient);
	void AddSession(sockaddr_in& a_rClient);
	void DeleteSession(u64 a_nSessionID);
};
