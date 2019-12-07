#include "stdafx.h"


CScene::CScene()
{
	this->m_nSceneID = 0;
	this->m_pCamera = NULL;
	this->m_nGUIDIdx = 0;
	this->m_pSkyBox = NULL;
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

	CActor* pActor = new CActor();
	CMaterialStandard* pMaterial = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_STANDARD);
	CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_DIFFUSE);
	pMaterial->AddTexture(pTexture);
	pActor->InitRenderer(pMeshShip, pMaterial);
	CShipControl::GetSingleton().pActor = pActor;

	PRegister msgSend;
	msgSend.SetValue(126);
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
	CShipControl::GetSingleton().pActor->Update();
}


