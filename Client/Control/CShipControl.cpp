#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CShipControl)

CShipControl::CShipControl()
{
	this->m_nID = -1;
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
			this->pActor->m_bullet->Launch(this->pActor->m_vPosition, this->pActor->m_vTowards);
		}
	}
	
}

void CShipControl::ControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{

}

void CShipControl::ControlCursor(f64 a_fX, f64 a_fY)
{

}
