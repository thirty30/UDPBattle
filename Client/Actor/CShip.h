#pragma once

class CShip : public CSceneObject
{
public:
	CShip();
	~CShip();

	virtual void Init();
	virtual void Update(f32 fDeltaTime);
	
	void ClientActorMove(f32 fDeltaTime);
	void ServerActorMove(f32 fDeltaTime);
};


