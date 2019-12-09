#pragma once

class CActor : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	CActor();
	~CActor();

	glm::vec3 m_vTowards;
	n8 m_nAction;
	tbool m_bFirstUpdate;
	CBullet* m_bullet;

	void Update(f32 fDeltaTime);
	void Move(f32 fDeltaTime);
};

