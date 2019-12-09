#include "stdafx.h"

CActor::CActor() : CPhysicsObject(this), CGraphicsObject(this)
{
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
	this->m_bFirstUpdate = false;
}

CActor::~CActor()
{

}

void CActor::Update(f32 fDeltaTime)
{
	this->Move(fDeltaTime);
	this->m_bullet->Update(fDeltaTime);
}

void CActor::Move(f32 fDeltaTime)
{
	if ((this->m_nAction & ACTION_FRONT) == ACTION_FRONT)
	{
		this->m_vPosition += this->m_vTowards * PLAYER_VELOCITY * fDeltaTime;
	}

	if ((this->m_nAction & ACTION_BACK) == ACTION_BACK)
	{
		this->m_vPosition += -this->m_vTowards * PLAYER_VELOCITY * fDeltaTime;
	}

	if ((this->m_nAction & ACTION_LEFT) == ACTION_LEFT)
	{
		glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
		f32 fYAngle = glm::radians(PLAYER_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		this->m_vTowards = vFront;
		this->UpdateRotation(glm::vec3(0.0f, PLAYER_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}

	if ((this->m_nAction & ACTION_RIGHT) == ACTION_RIGHT)
	{
		glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
		f32 fYAngle = glm::radians(-PLAYER_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		this->m_vTowards = vFront;
		this->UpdateRotation(glm::vec3(0.0f, -PLAYER_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}
}
