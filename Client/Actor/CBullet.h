#pragma once

class CBullet : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	glm::vec3 m_vVelocity;
	f32 m_fLifeTime;

public:
	CBullet();
	~CBullet();

	void Update(f32 a_fDeltaTime);
	void Launch(glm::vec3 a_vPos, glm::vec3 a_vTowards);
};
