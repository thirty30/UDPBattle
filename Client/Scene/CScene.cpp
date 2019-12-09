#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
	this->m_pSkyBox = NULL;
	this->m_fLastFrameTime = 0;
	this->m_fLastSyncTime = 0;
}

CScene::~CScene()
{

}

tbool CScene::Init()
{
	this->m_pCameraControl = new CCameraControl();
	this->m_pShipControl = new CShipControl();

	return true;
}

u64 CScene::GenGUID()
{
	return (++this->m_nGUIDIdx);
}

tbool CScene::LoadScene()
{
	//initialize camera
	n32 nScreenWidth = CGame::GetSingleton().GetScreenWidth();
	n32 nScreenHigh = CGame::GetSingleton().GetScreenHigh();
	f32 fScreenRatio = 1.0f * nScreenWidth / nScreenHigh;
	this->m_pCamera = new CCamera(this->GenGUID(), 0.6f, fScreenRatio, 3.0f, 100000.0f);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 200, -280);
	//this->m_pCamera->m_vPosition = glm::vec3(0, 5, -10);
	//this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.8f, 1.0f));

	this->m_pCamera->m_vPosition = glm::vec3(0, 400, -400);
	this->m_pCamera->m_vTowards = glm::normalize(glm::vec3(0.0f, -0.5f, 0.5f));
	TMuffin_AddCamera(this->m_pCamera);

	//Mesh
	CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);
	CMesh* pMeshSkyBox = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SKYBOX);
	CMesh* pMeshShip = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SHIP);
	

	//SkyBox
	n32 nShaderSkyBox = CResourceManager::GetSingleton().GetShaderID(E_SHADER_ID_SKYBOX);
	this->m_pSkyBox = new CSkyBox();
	this->m_pSkyBox->Init(pMeshSkyBox, nShaderSkyBox,
		"../Assets/Textures/SkyBox/Space/SpaceBoxX.png", "../Assets/Textures/SkyBox/Space/SpaceBoxNegX.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxY.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegY.png",
		"../Assets/Textures/SkyBox/Space/SpaceBoxZ.png", "../Assets/Textures/SkyBox/space/SpaceBoxNegZ.png"
		);
	TMuffin_SetSkyBox(this->m_pSkyBox);

	//scene items
	CDirectionLight* pDirectionLight = new CDirectionLight();

	for (n32 i = 0; i < 4; i++)
	{
		this->m_pActorArray[i] = new CActor();
		CMaterialStandard* pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_STANDARD);
		CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_DIFFUSE);
		pMaterial->AddTexture(pTexture);
		this->m_pActorArray[i]->InitRenderer(pMeshShip, pMaterial);

		CBullet* pBullet = new CBullet();
		CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);
		CMaterialDefault* pMaterialBullet = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BULLET);
		pMaterialBullet->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		pBullet->InitRenderer(pMeshSphere, pMaterialBullet);
		this->m_pActorArray[i]->m_bullet = pBullet;
	}	
	
	for (n32 i = 0; i < 4; i++)
	{
		this->m_pServerActorArray[i] = new CActor();
		CMaterialDefault* pMaterial = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
		pMaterial->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		this->m_pServerActorArray[i]->InitRenderer(pMeshShip, pMaterial);

		CBullet* pBullet = new CBullet();
		CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);
		pMaterial = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
		pBullet->InitRenderer(pMeshSphere, pMaterial);
		pBullet->SetEnable(true);
		this->m_pServerActorArray[i]->m_bullet = pBullet;
	}

	PRegister msgSend;
	msgSend.SetValue(0);
	CGame::GetSingleton().SendToServer(C2S_REGISTER, msgSend);

	return true;
}

void CScene::Clear()
{
	if (this->m_pCamera != NULL)
	{
		delete this->m_pCamera;
	}
	if (this->m_pCameraControl != NULL)
	{
		delete this->m_pCameraControl;
	}
}

void CScene::Loop()
{
	f32 fNowTime = TMuffin_GetNowFrameTime();
	f32 fDeltaTime = fNowTime - this->m_fLastFrameTime;
	if (fDeltaTime < (1.0f / 60))
	{
		return;
	}
	this->m_fLastFrameTime = fNowTime;

	//fDeltaTime = 1.0f / 60;
	CActor* pSelf = CShipControl::GetSingleton().pActor;
	if (pSelf != NULL)
	{
		pSelf->Update(fDeltaTime);

		if (fNowTime - this->m_fLastSyncTime >= (1 / RESURGENCE_TIME))
		{
			PPlayerAction msgSend;
			msgSend.SetAction(pSelf->m_nAction);
			msgSend.SetX(pSelf->m_vPosition.x);
			msgSend.SetZ(pSelf->m_vPosition.z);
			msgSend.SetRY(pSelf->m_qRotation.y);
			msgSend.SetRW(pSelf->m_qRotation.w);
			msgSend.SetTX(pSelf->m_vTowards.x);
			msgSend.SetTZ(pSelf->m_vTowards.z);
			CGame::GetSingleton().SendToServer(C2S_PLAYER_ACTION, msgSend);
			this->m_fLastSyncTime = fNowTime;
		}
	}
	for (n32 i = 0; i < 4; i++)
	{
		this->m_pActorArray[i]->Update(fDeltaTime);
		this->m_pServerActorArray[i]->Update(fDeltaTime);
	}
}


