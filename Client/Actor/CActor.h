#pragma once

class CActor : public CGameObject, public CPhysicsObject, public CGraphicsObject
{
public:
	CActor();
	~CActor();
	glm::vec3 m_vTowards;
	n8 m_nControlFlag[4] = { 0 };
	f32 m_fVeloctiy;
	f32 m_fRoataionVelocity;

	virtual void Update();

	void MoveFront();
	void MoveBack();
	void TurnLeft();
	void TurnRight();
};

