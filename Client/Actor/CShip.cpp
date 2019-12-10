#include "stdafx.h"

CShip::CShip()
{

}

CShip::~CShip()
{

}

void CShip::Init()
{
	CMesh* pMeshShip = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SHIP);

	this->m_pClientActor = new CActor();
	CMaterialStandard* pM1 = (CMaterialStandard*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_STANDARD);
	CTexture* pTexture = CResourceManager::GetSingleton().FindTexture(E_TEXTURE_ID_DIFFUSE);
	pM1->AddTexture(pTexture);
	this->m_pClientActor->InitRenderer(pMeshShip, pM1);

	this->m_pServerActor = new CActor();
	CMaterialDefault* pM2 = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
	pM2->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	this->m_pServerActor->InitRenderer(pMeshShip, pM2);
	this->m_pServerActor->SetEnable(false);
}

void CShip::Update(f32 fDeltaTime)
{
	this->ClientActorMove(fDeltaTime);
	//this->ServerActorMove(fDeltaTime);
}

void CShip::ClientActorMove(f32 fDeltaTime)
{
	CActor* pActor = this->m_pClientActor;
	n8 nAction = pActor->m_nAction;
	glm::vec3 vTowards = pActor->m_vTowards;

	if ((nAction & ACTION_FRONT) == ACTION_FRONT)
	{
		pActor->m_vPosition += vTowards * SHIP_VELOCITY * fDeltaTime;
	}

	if ((nAction & ACTION_BACK) == ACTION_BACK)
	{
		pActor->m_vPosition += -vTowards * SHIP_VELOCITY * fDeltaTime;
	}

	if ((nAction & ACTION_LEFT) == ACTION_LEFT)
	{
		glm::vec4 vFront = glm::vec4(vTowards, 1.0f);
		f32 fYAngle = glm::radians(SHIP_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		pActor->m_vTowards = vFront;
		pActor->UpdateRotation(glm::vec3(0.0f, SHIP_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}

	if ((nAction & ACTION_RIGHT) == ACTION_RIGHT)
	{
		glm::vec4 vFront = glm::vec4(vTowards, 1.0f);
		f32 fYAngle = glm::radians(-SHIP_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		pActor->m_vTowards = vFront;
		pActor->UpdateRotation(glm::vec3(0.0f, -SHIP_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}
}

void CShip::ServerActorMove(f32 fDeltaTime)
{
	CActor* pActor = this->m_pServerActor;
	n8 nAction = pActor->m_nAction;
	glm::vec3 vTowards = pActor->m_vTowards;

	if ((nAction & ACTION_FRONT) == ACTION_FRONT)
	{
		pActor->m_vPosition += vTowards * SHIP_VELOCITY * fDeltaTime;
	}

	if ((nAction & ACTION_BACK) == ACTION_BACK)
	{
		pActor->m_vPosition += -vTowards * SHIP_VELOCITY * fDeltaTime;
	}

	if ((nAction & ACTION_LEFT) == ACTION_LEFT)
	{
		glm::vec4 vFront = glm::vec4(vTowards, 1.0f);
		f32 fYAngle = glm::radians(SHIP_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		pActor->m_vTowards = vFront;
		pActor->UpdateRotation(glm::vec3(0.0f, SHIP_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}

	if ((nAction & ACTION_RIGHT) == ACTION_RIGHT)
	{
		glm::vec4 vFront = glm::vec4(vTowards, 1.0f);
		f32 fYAngle = glm::radians(-SHIP_ROTATION_VELOCITY * fDeltaTime);
		glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		vFront = matRotY * vFront;
		pActor->m_vTowards = vFront;
		pActor->UpdateRotation(glm::vec3(0.0f, -SHIP_ROTATION_VELOCITY * fDeltaTime, 0.0f));
	}
}

