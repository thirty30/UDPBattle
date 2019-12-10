#include "stdafx.h"

CActor::CActor() : CGraphicsObject(this)
{
	this->m_nAction = 0;
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
}

CActor::~CActor()
{

}
