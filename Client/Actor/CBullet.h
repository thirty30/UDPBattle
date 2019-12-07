#pragma once

class CBullet : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	glm::vec3 m_vVelocity;

public:
	CBullet();
	~CBullet();
};
