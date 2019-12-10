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
		if (rPlayer.m_bIsDead == true)
		{
			continue;
		}
		rPlayer.Move(a_fDeltaTime);
		rPlayer.UpdateBullet(a_fDeltaTime);

		for (n32 j = 0; j < 4; j++)
		{
			CPlayer& rTargetPlayer = this->m_PlayerArray[j];
			f32 fDis = glm::distance(rTargetPlayer.m_vPosition, rPlayer.m_bullet.m_vPosition);
			if (fDis <= BULLET_HIT_RADIUS && rPlayer.m_bullet.m_bIsActive == true && i != j)
			{
				rTargetPlayer.m_bIsDead = true;
			}
		}
	}

	this->SyncPlayerState(a_fNowTime);
}

void CBattle::SyncPlayerState(f32 a_fNowTime)
{
	f32 fDeltaTime = a_fNowTime - this->m_fLastFrameTime;
	if (fDeltaTime < (1.0f / RESURGENCE_TIME))
	{
		return;
	}
	this->m_fLastFrameTime = a_fNowTime;

	PPlayerStateList msgSend;
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		rPlayer.PacketInfo(msgSend);
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

void CBattle::PlayerAction(CSession* a_pSession, PPlayerAction& a_rMsg)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession != a_pSession)
		{
			continue;
		}
		rPlayer.m_nAction = a_rMsg.GetAction();
		rPlayer.m_vPosition.x = a_rMsg.GetX();
		rPlayer.m_vPosition.z = a_rMsg.GetZ();
		rPlayer.m_vTowards.x = a_rMsg.GetTX();
		rPlayer.m_vTowards.z = a_rMsg.GetTZ();
		rPlayer.m_qRotation = glm::quat(a_rMsg.GetRW(), 0.0f, a_rMsg.GetRY(), 0.0f);
	}
}

void CBattle::PlayerBullet(CSession* a_pSession)
{
	for (n32 i = 0; i < 4; i++)
	{
		CPlayer& rPlayer = this->m_PlayerArray[i];
		if (rPlayer.m_pSession != a_pSession)
		{
			continue;
		}
		rPlayer.LaunchBullet();
	}
}

