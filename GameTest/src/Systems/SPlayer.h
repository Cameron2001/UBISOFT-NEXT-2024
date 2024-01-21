#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
class SPlayer : public ISystem
{
public:
    void Update(Scene& scene, float dt);
};
