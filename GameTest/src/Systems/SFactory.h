#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"

class SFactory : public ISystem
{
public:
    void CreateWall();
    void CreatePlayer(Scene* scene, vec2 pos, vec2 bounds);
    void CreateEnemy();
    void CreateButton();
    void CreateLevelBounds();
    void CreateBox(Scene* scene, vec2 pos, vec2 bounds);
    void CreateCircle(Scene* scene, vec2 pos, float radius);
    void CreateCamera(Scene* scene, vec2 pos);
    
};
