#include "stdafx.h"
#include "SPlayer.h"

void SPlayer::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CPlayer>())
    {
        CTransform transform = scene->m_register.GetComponent<CTransform>(entityID);
        CPlayer player = scene->m_register.GetComponent<CPlayer>(entityID);
        CRigidbody rigidbody = scene->m_register.GetComponent<CRigidbody>(entityID);
    }
}


