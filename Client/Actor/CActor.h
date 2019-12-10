#pragma once

class CActor : public CGameObject, public CGraphicsObject
{
public:
	n8 m_nAction;
	glm::vec3 m_vTowards;

	CActor();
	~CActor();
};

