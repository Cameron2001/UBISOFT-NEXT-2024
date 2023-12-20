#pragma once
#include "ISystem.h"
#include "../Components/CPlayer.h"
#include "../Components/CRigidbody.h"
#include "../Components/CTransform.h"
#include "../Components/CRender.h"
#include "../Core/Scene.h"
class SPlayer : public ISystem
{
public:
    void Update(Scene* scene);
private:
    float m_moveSpeed = 25.0f;
    
    
};
