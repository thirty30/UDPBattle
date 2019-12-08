#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CBattle)

CBattle::CBattle()
{
	this->m_fLastFrameTime = 0;
}

CBattle::~CBattle()
{

}

tbool CBattle::Init()
{
	// init players
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		rPlayer.m_nPlayerID = i;
		rPlayer.m_eState = E_PLAYER_STATE_BOT;
		rPlayer.InitPosition();
	}
	return true;
}

void CBattle::Update(f32 a_fNowTime, f32 a_fDeltaTime)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_eState == E_PLAYER_STATE_DEAD)
		{
			continue;
		}
		rPlayer.Move(a_fDeltaTime);
	}

	this->SyncPlayerState(a_fNowTime);
}

void CBattle::SyncPlayerState(f32 a_fNowTime)
{
	f32 fDeltaTime = a_fNowTime - this->m_fLastFrameTime;
	if (fDeltaTime < (1.0f / 5))
	{
		return;
	}
	this->m_fLastFrameTime = a_fNowTime;

	PPlayerStateList msgSend;
	for (n32 i = 0; i < 4; i++)
	{
		PPlayerState* pState = msgSend.appendPlayerState();

		CPlayer& rPlayer = this->m_PlayerArray[i];
		rPlayer.PacketInfo(pState);
	}
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession == NULL)
		{
			continue;
		}
		CServer::GetSingleton().SendToClient(S2C_SYNC_PLAYER_STATE, rPlayer.m_pSession->m_nSessionID, msgSend);
	}
}

void CBattle::AddPlayer(CSession* a_pSession)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession == NULL)
		{
			rPlayer.m_pSession = a_pSession;
			rPlayer.m_eState = E_PLAYER_STATE_PLAYER;
			rPlayer.m_nAction = 0;

			PRegisterResp msgSend;
			msgSend.SetValue(rPlayer.m_nPlayerID);
			CServer::GetSingleton().SendToClient(S2C_REGISTER_RESP, rPlayer.m_pSession->m_nSessionID, msgSend);
			return;
		}
	}
}

void CBattle::DeletePlayer(u64 a_nSID)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession != NULL && rPlayer.m_pSession->m_nSessionID == a_nSID)
		{
			rPlayer.m_pSession = NULL;
			rPlayer.m_eState = E_PLAYER_STATE_BOT;
			rPlayer.InitPosition();
		}
	}
}

void CBattle::PlayerAction(CSession* a_pSession, n8 a_nAction)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession != a_pSession)
		{
			continue;
		}
		rPlayer.m_nAction = a_nAction;
	}
}

