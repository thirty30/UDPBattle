#include "stdafx.h"

CActor::CActor() : CPhysicsObject(this), CGraphicsObject(this)
{
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
	this->m_fVeloctiy = 100.0f;
	this->m_fRoataionVelocity = 100.0f;
}

CActor::~CActor()
{

}

void CActor::Update()
{
	if (this->m_nControlFlag[0] == 1)
	{
		this->MoveFront();
	}
	if (this->m_nControlFlag[1] == 1)
	{
		this->MoveBack();
	}
	if (this->m_nControlFlag[2] == 1)
	{
		this->TurnLeft();
	}
	if (this->m_nControlFlag[3] == 1)
	{
		this->TurnRight();
	}
}

void CActor::MoveFront()
{
	this->m_vPosition += this->m_vTowards * this->m_fVeloctiy * TMuffin_GetDeltaFrameTime();
}

void CActor::MoveBack()
{
	this->m_vPosition += -this->m_vTowards * this->m_fVeloctiy * TMuffin_GetDeltaFrameTime();
}

void CActor::TurnLeft()
{
	glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
	f32 fYAngle = glm::radians(this->m_fRoataionVelocity * TMuffin_GetDeltaFrameTime());
	glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	vFront = matRotY * vFront;
	this->m_vTowards = vFront;
	this->UpdateRotation(glm::vec3(0.0f, this->m_fRoataionVelocity * TMuffin_GetDeltaFrameTime(), 0.0f));
}

void CActor::TurnRight()
{
	glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
	f32 fYAngle = glm::radians(-this->m_fRoataionVelocity * TMuffin_GetDeltaFrameTime());
	glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	vFront = matRotY * vFront;
	this->m_vTowards = vFront;
	this->UpdateRotation(glm::vec3(0.0f, -this->m_fRoataionVelocity * TMuffin_GetDeltaFrameTime(), 0.0f));
}
