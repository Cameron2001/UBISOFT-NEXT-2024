#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"
class SPlayer : public ISystem
{
public:
    void Update(Scene* scene);
private:
    float m_moveSpeed = 25.0f;
    
    
};
