#include "stdafx.h"

void CGame::HandlerRegisterResp(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PRegisterResp msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	n8 nID = msgRecv.GetValue();
	CShipControl::GetSingleton().pActor = CGame::GetSingleton().GetCurrentScene()->m_pActorArray[nID];
	CShipControl::GetSingleton().m_nID = nID;
}

void CGame::HandlerSyncPlayerState(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PPlayerStateList msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	for (n32 i = 0; i < msgRecv.GetPlayerStateCount(); i++)
	{
		const PPlayerState* pState = msgRecv.GetPlayerStateAt(i);
		CActor* pActor = CGame::GetSingleton().GetCurrentScene()->m_pActorArray[pState->GetID()];
		if (CShipControl::GetSingleton().m_nID == i)
		{
			continue;
		}

		if (pState->GetState() == 2)
		{
			pActor->SetEnable(false);
			continue;
		}

		pActor->SetEnable(true);
		pActor->m_vPosition = glm::vec3(pState->GetX(), 0.0f, pState->GetZ());
		pActor->SetRotation(glm::quat(pState->GetRW(), 0.0f, pState->GetRY(), 0.0f));
		pActor->m_vTowards = glm::vec3(pState->GetTX(), 0.0f, pState->GetTZ());

		pActor->m_nAction = pState->GetAction();
	}
	
	for (n32 i = 0; i < msgRecv.GetPlayerStateCount(); i++)
	{
		const PPlayerState* pState = msgRecv.GetPlayerStateAt(i);
		CActor* pActor = CGame::GetSingleton().GetCurrentScene()->m_pServerActorArray[pState->GetID()];
		pActor->m_vPosition = glm::vec3(pState->GetX(), 0.0f, pState->GetZ());
		pActor->SetRotation(glm::quat(pState->GetRW(), 0.0f, pState->GetRY(), 0.0f));

		if (pState->GetBActive() == 1)
		{
			pActor->m_bullet->SetEnable(true);
			pActor->m_bullet->m_vPosition = glm::vec3(pState->GetBX(), 0.0f, pState->GetBZ());
			//pActor->m_bullet->m_vVelocity = glm::vec3(pState->GetBTX(), 0.0f, pState->GetBTZ()) * BULLET_VELOCITY;
		}
		else
		{
			pActor->m_bullet->SetEnable(false);
		}	
	}
}
