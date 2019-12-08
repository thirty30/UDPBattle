#include "stdafx.h"

void CGame::HandlerRegisterResp(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PRegisterResp msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	n8 nID = msgRecv.GetValue();
	CShipControl::GetSingleton().pActor = CGame::GetSingleton().GetCurrentScene()->m_pActorArray[nID];
}

void CGame::HandlerSyncPlayerState(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PPlayerStateList msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	for (n32 i = 0; i < msgRecv.GetPlayerStateCount(); i++)
	{
		const PPlayerState* pState = msgRecv.GetPlayerStateAt(i);
		CActor* pActor = CGame::GetSingleton().GetCurrentScene()->m_pActorArray[pState->GetID()];
		if (pActor->m_bFirstUpdate == false)
		{
			pActor->m_vPosition = glm::vec3(pState->GetX(), 0.0f, pState->GetZ());
			pActor->SetRotation(glm::quat(pState->GetRX(), pState->GetRY(), pState->GetRZ(), pState->GetRW()));
			//glm::vec3 vAngle = pActor->GetEulerAngle();
			//glm::mat4 matRotY = glm::mat4(pActor->m_qRotation);
			//glm::vec4 vFront = matRotY * glm::vec4(pActor->m_vTowards, 1.0f);
			//pActor->m_vTowards = vFront;
		
			pActor->m_vTowards = glm::vec3(pState->GetTX(), 0.0f, pState->GetTZ());;
			pActor->m_bFirstUpdate = true;
			pActor->Debug();
		}
		pActor->m_nAction = pState->GetAction();
	}
	
	//for (n32 i = 0; i < msgRecv.GetPlayerStateCount(); i++)
	//{
	//	const PPlayerState* pState = msgRecv.GetPlayerStateAt(i);
	//	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->m_pServerActorArray[pState->GetID()];
	//	pActor->m_vPosition = glm::vec3(pState->GetX(), 0.0f, pState->GetZ());
	//	pActor->SetRotation(glm::quat(pState->GetRX(), pState->GetRY(), pState->GetRZ(), pState->GetRW()));
	//}
}
