#include "stdafx.h"


CBullet::CBullet() : CPhysicsObject(this), CGraphicsObject(this)
{
	this->SetEnable(false);
	this->m_fLifeTime = 0;
}

CBullet::~CBullet()
{

}

void CBullet::Update(f32 a_fDeltaTime)
{
	if (this->IsEnable() == false)
	{
		return;
	}

	this->m_vPosition += this->m_vVelocity * a_fDeltaTime;
	this->m_fLifeTime += a_fDeltaTime;
	if (this->m_fLifeTime >= BULLET_LIFE_TIME)
	{
		this->m_fLifeTime = 0.0f;
		this->SetEnable(false);
	}
	
}

void CBullet::Launch(glm::vec3 a_vPos, glm::vec3 a_vTowards)
{
	if (this->m_fLifeTime > 0)
	{
		return;
	}

	this->SetEnable(true);
	this->m_vPosition = a_vPos;
	this->m_vVelocity = a_vTowards * BULLET_VELOCITY;
	PMessageN8 msgSend;
	CGame::GetSingleton().SendToServer(C2S_PLAYER_BULLET, msgSend);
}
