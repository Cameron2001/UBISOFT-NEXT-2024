#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
class SPlayer : public ISystem
{
public:
    void Init();
    void Update(Scene* scene, float dt);
    Entity GetPlayer();
private:
    Entity m_player;
};
