#pragma once

class CScene : public CSingleton<CScene>
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;
	CShipControl* m_pShipControl;
	u64 m_nGUIDIdx;
	CSkyBox* m_pSkyBox;
	f32 m_fLastFrameTime;
	f32 m_fLastSyncTime;

private:
	u64 GenGUID();

public:
	CSceneObject* m_pObjArray[8];
	n8 m_nPlayerID;

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();
	void Loop();

	CCamera* GetCamera() { return this->m_pCamera; }
	CActor* GetPlayerActor();
	CActor* GetClientActor(n32 a_nIdx) { return this->m_pObjArray[a_nIdx]->m_pClientActor; }
	CActor* GetServerActor(n32 a_nIdx) { return this->m_pObjArray[a_nIdx]->m_pServerActor; }
	
};


