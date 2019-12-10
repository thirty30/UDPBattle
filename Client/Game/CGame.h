#pragma once

class CGame : public CSingleton<CGame>
{
private:
	n32 m_nScreenWidth;
	n32 m_nScreenHigh;
	tstring m_strWindowName;
	CScene* m_pScene;
	EGameStatus m_eGameStatus;
	CResourceManager* m_pResManager;

	SOCKET m_nSocketFD;
	sockaddr_in m_sockAddr;
	TMessageSendHeap m_SendHeap;
	tcchar* m_pSendBuffer;
	tcchar* m_pReceiveBuffer;
	n32 m_nPort;

#include "./MessageHandler.h"

public:
	static void GameLogicCallBack() { CGame::GetSingleton().GameLogicLoop(); }
	
public:
	CGame();
	~CGame();

	tbool InitGame();
	void ClearGame();
	void LoopGame();
	void SetUDPPort(n32 a_nPort) { this->m_nPort = a_nPort; }

	/////////////////////////////////////////////////////////////////
	tbool InitNet();
	void LoopNet();
	void OnReceived(tcchar* a_pData, n32 a_nSize);
	void SendToServer(u32 a_uMsgID, const PMessageBase& a_Msg);
	void SendToServer(u32 a_uMsgID, const tcchar* a_pData, u32 a_uLen);
	/////////////////////////////////////////////////////////////////

	void SetScreenSize(n32 a_nWidth, n32 a_nHigh);
	inline n32 GetScreenWidth() { return this->m_nScreenWidth; }
	inline n32 GetScreenHigh() { return this->m_nScreenHigh; }
	CScene* GetCurrentScene() { return this->m_pScene; }
	CResourceManager* GetResourceManager() { return this->m_pResManager; }
	void GameLogicLoop();
	
};



