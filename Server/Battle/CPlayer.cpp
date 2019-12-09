#include "stdafx.h"


CPlayer::CPlayer()
{
	this->m_pSession = NULL;
	this->m_nAction = 0;
	this->m_qRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
}

CPlayer::~CPlayer()
{

}

void CPlayer::InitPosition()
{
	this->m_vPosition = RandPosition();
	this->m_vTargetPosition = RandPosition();
}

void CPlayer::BotMove()
{
	this->m_nAction = 0;
	this->m_nAction |= ACTION_FRONT;
	glm::vec3 vTargetDirection = glm::normalize(this->m_vTargetPosition - this->m_vPosition);
	f32 fCos = glm::dot(this->m_vTowards, vTargetDirection);
	if (fCos < 0.99f)
	{
		this->m_nAction |= ACTION_LEFT;
	}

	f32 fDis = glm::distance(this->m_vPosition, this->m_vTargetPosition);
	if (fDis <= 5.0f)
	{
		this->m_vTargetPosition = RandPosition();
	}
}

void CPlayer::PacketInfo(PPlayerState* a_pState)
{
	a_pState->SetID(this->m_nPlayerID);
	a_pState->SetState((n8)this->m_eState);
	a_pState->SetAction(this->m_nAction);
	a_pState->SetX(this->m_vPosition.x);
	a_pState->SetZ(this->m_vPosition.z);
	a_pState->SetRY(this->m_qRotation.y);
	a_pState->SetRW(this->m_qRotation.w);
	a_pState->SetTX(this->m_vTowards.x);
	a_pState->SetTZ(this->m_vTowards.z);
	a_pState->SetBActive(this->m_bullet.m_bIsActive);
	a_pState->SetBX(this->m_bullet.m_vPosition.x);
	a_pState->SetBZ(this->m_bullet.m_vPosition.z);
	a_pState->SetBTX(this->m_bullet.m_vTowards.x);
	a_pState->SetBTZ(this->m_bullet.m_vTowards.z);
}

void CPlayer::Move(f32 a_fDeltaTime)
{
	if (this->m_eState == E_PLAYER_STATE_BOT)
	{
		this->BotMove();
	}

	if ((this->m_nAction & ACTION_FRONT) == ACTION_FRONT)
	{
		this->m_vPosition += this->m_vTowards * PLAYER_VELOCITY * a_fDeltaTime;
	}

	if ((this->m_nAction & ACTION_BACK) == ACTION_BACK)
	{
		this->m_vPosition += -this->m_vTowards * PLAYER_VELOCITY * a_fDeltaTime;
	}

	if ((this->m_nAction & ACTION_LEFT) == ACTION_LEFT)
	{
		glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
		f32 fYAngle = glm::radians(PLAYER_ROTATION_VELOCITY * a_fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		this->m_vTowards = vFront;
		this->UpdateRotation(glm::vec3(0.0f, PLAYER_ROTATION_VELOCITY * a_fDeltaTime, 0.0f));
	}

	if ((this->m_nAction & ACTION_RIGHT) == ACTION_RIGHT)
	{
		glm::vec4 vFront = glm::vec4(this->m_vTowards, 1.0f);
		f32 fYAngle = glm::radians(-PLAYER_ROTATION_VELOCITY * a_fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		this->m_vTowards = vFront;
		this->UpdateRotation(glm::vec3(0.0f, -PLAYER_ROTATION_VELOCITY * a_fDeltaTime, 0.0f));
	}
}

void CPlayer::LaunchBullet()
{
	if (this->m_bullet.m_bIsActive == true)
	{
		return;
	}
	this->m_bullet.m_bIsActive = true;
	this->m_bullet.m_vPosition = this->m_vPosition;
	this->m_bullet.m_vTowards = this->m_vTowards;
}

void CPlayer::UpdateBullet(f32 a_fDeltaTime)
{
	if (this->m_bullet.m_bIsActive == false)
	{
		return;
	}
	this->m_bullet.m_vPosition += this->m_bullet.m_vTowards * BULLET_VELOCITY * a_fDeltaTime;
	this->m_bullet.m_fLifeTime += a_fDeltaTime;
	if (this->m_bullet.m_fLifeTime >= BULLET_LIFE_TIME)
	{
		this->m_bullet.m_fLifeTime = 0.0f;
		this->m_bullet.m_bIsActive = false;
	}
}

void CPlayer::UpdateRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);
	this->m_qRotation *= glm::quat(vAngle);
}

glm::vec3 CPlayer::GetEulerAngle()
{
	return glm::eulerAngles(this->m_qRotation);
}
