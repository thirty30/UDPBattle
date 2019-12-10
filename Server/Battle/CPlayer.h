#pragma once

class CBullet
{
public:
	tbool m_bIsActive;
	glm::vec3 m_vPosition;
	glm::vec3 m_vTowards;
	f32 m_fLifeTime;

	CBullet()
	{
		this->m_bIsActive = false;
		this->m_fLifeTime = 0.0f;
	}
	~CBullet() {}
};

class CPlayer
{
public:
	n8 m_nPlayerID;
	CSession* m_pSession;
	EPlayerState m_eState;
	glm::vec3 m_vPosition;
	glm::vec3 m_vTargetPosition;
	glm::vec3 m_vTowards;
	f32 m_fDeadTime;
	n8  m_nAction;
	glm::quat m_qRotation;
	tbool m_bIsDead;

	CBullet m_bullet;

	CPlayer();
	~CPlayer();

	void PacketInfo(PPlayerStateList& a_rMsg);

	void InitPosition();
	void BotMove();

	void Move(f32 a_fDeltaTime);
	void LaunchBullet();
	void UpdateBullet(f32 a_fDeltaTime);

	void UpdateRotation(glm::vec3 a_vEulerAngle);
	glm::vec3 GetEulerAngle();
};
