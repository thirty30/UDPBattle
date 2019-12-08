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
	
	if (a_nKey == GLFW_KEY_W)
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->pActor->m_nAction |= ACTION_FRONT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->pActor->m_nAction ^= ACTION_FRONT;
		}
	}

	if (a_nKey == GLFW_KEY_S)
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->pActor->m_nAction |= ACTION_BACK;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->pActor->m_nAction ^= ACTION_BACK;
		}
	}

	if (a_nKey == GLFW_KEY_A)
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->pActor->m_nAction |= ACTION_LEFT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->pActor->m_nAction ^= ACTION_LEFT;
		}
	}

	if (a_nKey == GLFW_KEY_D)
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->pActor->m_nAction |= ACTION_RIGHT;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->pActor->m_nAction ^= ACTION_RIGHT;
		}
	}

	if (a_nKey == GLFW_KEY_SPACE)
	{
		if (a_nAction == GLFW_PRESS)
		{
			CBullet* pBullet = new CBullet();
			pBullet->m_vVelocity = this->pActor->m_vTowards * 100.0f;
		}
	}
	
}

void CShipControl::ControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{

}

void CShipControl::ControlCursor(f64 a_fX, f64 a_fY)
{

}
