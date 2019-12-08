#pragma once


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

	CPlayer();
	~CPlayer();

	void PacketInfo(PPlayerState* a_pState);

	void InitPosition();
	void BotMove();

	void Move(f32 a_fDeltaTime);

	void UpdateRotation(glm::vec3 a_vEulerAngle);
	glm::vec3 GetEulerAngle();
};
