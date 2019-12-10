#pragma once

class CBullet : public CSceneObject
{
public:
	CBullet();
	~CBullet();

	virtual void Init();
	virtual void Update(f32 a_fDeltaTime);
};
