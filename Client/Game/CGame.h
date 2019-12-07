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

public:
	static void PhysicsCallBack() { CGame::GetSingleton().PhysicsLoop(); }
	static void GameLogicCallBack() { CGame::GetSingleton().GameLogicLoop(); }
	
public:
	CGame();
	~CGame();

	tbool InitGame();
	void ClearGame();
	void LoopGame();
	tbool InitNet();
	void LoopNet();

	void SetScreenSize(n32 a_nWidth, n32 a_nHigh);
	inline n32 GetScreenWidth() { return this->m_nScreenWidth; }
	inline n32 GetScreenHigh() { return this->m_nScreenHigh; }
	CScene* GetCurrentScene() { return this->m_pScene; }
	CResourceManager* GetResourceManager() { return this->m_pResManager; }
	void PhysicsLoop();
	void GameLogicLoop();
};



