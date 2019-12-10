#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CShipControl)

CShipControl::CShipControl()
{
}

CShipControl::~CShipControl()
{

}

void CShipControl::ControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	CActor* pActor = CScene::GetSingleton().GetPlayerActor();
	if (pActor == NULL)
	{
		return;
	}
	if (a_nKey == GLFW_KEY_W)
	{
		if (a_nAction == GLFW_PRESS)
		{
			pActor->m_nAction |= ACTION_FRONT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			pActor->m_nAction ^= ACTION_FRONT;
		}
	}

	if (a_nKey == GLFW_KEY_S)
	{
		if (a_nAction == GLFW_PRESS)
		{
			pActor->m_nAction |= ACTION_BACK;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			pActor->m_nAction ^= ACTION_BACK;
		}
	}

	if (a_nKey == GLFW_KEY_A)
	{
		if (a_nAction == GLFW_PRESS)
		{
			pActor->m_nAction |= ACTION_LEFT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			pActor->m_nAction ^= ACTION_LEFT;
		}
	}

	if (a_nKey == GLFW_KEY_D)
	{
		if (a_nAction == GLFW_PRESS)
		{
			pActor->m_nAction |= ACTION_RIGHT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			pActor->m_nAction ^= ACTION_RIGHT;
		}
	}

	if (a_nKey == GLFW_KEY_SPACE)
	{
		if (a_nAction == GLFW_PRESS)
		{
			PMessageN8 msgSend;
			CGame::GetSingleton().SendToServer(C2S_PLAYER_BULLET, msgSend);
		}
	}

	if (a_nKey == GLFW_KEY_R)
	{
		if (a_nAction == GLFW_PRESS)
		{
			PMessageN8 msgSend;
			CGame::GetSingleton().SendToServer(C2S_RESURGENCE, msgSend);
		}
	}
	
}

