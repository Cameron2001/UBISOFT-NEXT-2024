#include "stdafx.h"
#include "SRender.h"

void SRender::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CRender>())
    {
        CTransform transform = scene->m_register.GetComponent<CTransform>(entityID);
        CRender render = scene->m_register.GetComponent<CRender>(entityID);
    }
}
