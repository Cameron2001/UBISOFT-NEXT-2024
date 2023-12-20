#include "stdafx.h"
#include "SPlayer.h"

#include "../Components/CPlayer.h"

void SPlayer::Update(Scene* scene)
{
    for(auto entityID : scene->m_register.GetEntities<CPlayer>())
    {
        
    }
}


