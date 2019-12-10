#include "stdafx.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Init()
{
	CMesh* pMeshSphere = CResourceManager::GetSingleton().FindMesh(E_MODEL_ID_SPHERE);

	this->m_pClientActor = new CActor();
	CMaterialDefault* pM1 = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_BULLET);
	pM1->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	this->m_pClientActor->InitRenderer(pMeshSphere, pM1);

	this->m_pServerActor = new CActor();
	CMaterialDefault* pM2 = (CMaterialDefault*)CResourceManager::GetSingleton().FindMaterial(E_MATERIAL_ID_DEFAULT);
	this->m_pServerActor->InitRenderer(pMeshSphere, pM2);
}

void CBullet::Update(f32 a_fDeltaTime)
{
	this->m_pClientActor->m_vPosition += this->m_pClientActor->m_vTowards * BULLET_VELOCITY * a_fDeltaTime;

}
