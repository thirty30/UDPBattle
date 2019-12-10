#pragma once

class CSceneObject
{
public:
	n8 m_nID;
	CActor* m_pClientActor;
	CActor* m_pServerActor;

	CSceneObject() 
	{
		this->m_nID = 0; 
		this->m_pClientActor = NULL;
		this->m_pServerActor = NULL;
	}

	virtual ~CSceneObject() {}

	virtual void Init() T_PURE;
	virtual void Update(f32 a_fDeltaTime) T_PURE;
};


