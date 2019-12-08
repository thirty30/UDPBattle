#pragma once

class CBattle : public CSingleton<CBattle>
{
public:
	CPlayer m_PlayerArray[4];
	f32 m_fLastFrameTime;

public:
	CBattle();
	~CBattle();

	tbool Init();
	void Update(f32 a_fNowTime, f32 a_fDeltaTime);
	void SyncPlayerState(f32 a_fNowTime);
	void AddPlayer(CSession* a_pSession);
	void DeletePlayer(u64 a_nSID);
	void PlayerAction(CSession* a_pSession, n8 a_nAction);
};


