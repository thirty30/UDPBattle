#pragma once

class CScene
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;
	CShipControl* m_pShipControl;
	u64 m_nGUIDIdx;
	hash_map<u64, CGameObject*> m_mapID2GameObj;
	CSkyBox* m_pSkyBox;
	f32 m_fLastFrameTime;
	f32 m_fLastSyncTime;

public:
	CActor* m_pActorArray[4];
	CActor* m_pServerActorArray[4];

private:
	u64 GenGUID();

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();
	void Loop();

	CCamera* GetCamera() { return this->m_pCamera; }
};


