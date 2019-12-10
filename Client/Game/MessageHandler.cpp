#include "stdafx.h"

void CGame::HandlerRegisterResp(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PRegisterResp msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	CScene::GetSingleton().m_nPlayerID = msgRecv.GetValue();
}

// Actor
// 1byte: |3 bits: ID, 1 bit: IsDead, 4 bits: Action|
// 2byte: position x
// 2byte: position z
// 4byte: rotation y
// 2byte: towards x
// 2byte: towards z

// Bullet
// 1byte: |3 bits: ID, 1 bit: IsActive|
// 2byte: position x
// 2byte: position z
// 2byte: towards x
// 2byte: towards z

void CGame::HandlerSyncPlayerState(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PPlayerStateList msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	for (n32 i = 0; i < msgRecv.GetPlayerStateCount(); i++)
	{
		const PPlayerState* pState = msgRecv.GetPlayerStateAt(i);
		const tcchar* pData = pState->GetValue();
		n32 nDataLen = pState->GetValueSize();

		n8 nID = pData[0] & 7;
		tbool bIsDead = (pData[0] >> 3) & 1;
		n8 nAction = pData[0] >> 4;

		n16 nX, nZ, nTX, nTZ;
		f32 fX, fZ, fRY, fRW, fTX, fTZ;
		n32 nOffset = 1;
		TMemcpy((tcchar*)&nX, 2, pData + nOffset, 2); nOffset += 2; fX = nX / 100.0f;
		TMemcpy((tcchar*)&nZ, 2, pData + nOffset, 2); nOffset += 2; fZ = nZ / 100.0f;
		TMemcpy((tcchar*)&fRY, 4, pData + nOffset, 4); nOffset += 4; //fRW = glm::sqrt(1 - glm::pow(fRY, 2));
		TMemcpy((tcchar*)&fRW, 4, pData + nOffset, 4); nOffset += 4;
		TMemcpy((tcchar*)&nTX, 2, pData + nOffset, 2); nOffset += 2; fTX = nTX / 10000.0f;
		TMemcpy((tcchar*)&nTZ, 2, pData + nOffset, 2); nOffset += 2; fTZ = nTZ / 10000.0f;

		CActor* pClientActor = CScene::GetSingleton().GetClientActor(nID);
		CActor* pServerActor = CScene::GetSingleton().GetServerActor(nID);

		if (bIsDead == true)
		{
			pClientActor->SetEnable(false);
			pServerActor->SetEnable(false);
			continue;
		}

		pClientActor->SetEnable(true);
		pServerActor->SetEnable(true);

		if (nID != CScene::GetSingleton().m_nPlayerID)
		{
			pClientActor->m_nAction = nAction;
			pClientActor->m_vPosition = glm::vec3(fX, 0.0f, fZ);
			pClientActor->SetRotation(glm::quat(fRW, 0.0f, fRY, 0.0f));
			pClientActor->m_vTowards = glm::vec3(fTX, 0.0f, fTZ);
		}

		pServerActor->m_vPosition = glm::vec3(fX, 0.0f, fZ);
		pServerActor->SetRotation(glm::quat(fRW, 0.0f, fRY, 0.0f));
		pServerActor->m_vTowards = glm::vec3(fTX, 0.0f, fTZ);
	}
	
	for (n32 i = 0; i < msgRecv.GetBulletStateCount(); i++)
	{
		const PBulletState* pState = msgRecv.GetBulletStateAt(i);
		const tcchar* pData = pState->GetValue();
		n32 nDataLen = pState->GetValueSize();

		n8 nID = pData[0] & 7;
		tbool bIsActive = (pData[0] >> 3) & 1;

		n16 nX, nZ, nTX, nTZ;
		f32 fX, fZ, fTX, fTZ;
		n32 nOffset = 1;
		TMemcpy((tcchar*)&nX, 2, pData + nOffset, 2); nOffset += 2; fX = nX / 100.0f;
		TMemcpy((tcchar*)&nZ, 2, pData + nOffset, 2); nOffset += 2; fZ = nZ / 100.0f;
		TMemcpy((tcchar*)&nTX, 2, pData + nOffset, 2); nOffset += 2; fTX = nTX / 10000.0f;
		TMemcpy((tcchar*)&nTZ, 2, pData + nOffset, 2); nOffset += 2; fTZ = nTZ / 10000.0f;

		CActor* pClientActor = CScene::GetSingleton().GetClientActor(nID);
		CActor* pServerActor = CScene::GetSingleton().GetServerActor(nID);

		if (bIsActive == true)
		{
			pClientActor->SetEnable(true);
			pClientActor->m_vPosition = glm::vec3(fX, 0.0f, fZ);
			pClientActor->m_vTowards = glm::vec3(fTX, 0.0f, fTZ);

			pServerActor->SetEnable(true);
			pServerActor->m_vPosition = glm::vec3(fX, 0.0f, fZ);
			pServerActor->m_vTowards = glm::vec3(fTX, 0.0f, fTZ);
		}
		else
		{
			pClientActor->SetEnable(false);
			pServerActor->SetEnable(false);
		}
	}
}
