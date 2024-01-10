#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"

class SFactory : public ISystem
{
public:
    void CreateWall();
    Entity CreatePlayer(Scene* scene, vec2 pos, vec2 bounds, Entity id = NULL);
    Entity CreateButton(Scene* scene, vec2 pos, vec2 bounds, Entity id = NULL);
    void CreateEnemy();
    Entity CreateBox(Scene* scene, vec2 pos, vec2 bounds, Entity id = NULL);
    Entity CreateCircle(Scene* scene, vec2 pos, float radius, Entity id = NULL);
    Entity CreateCamera(Scene* scene, vec2 pos, Entity id = NULL);
    
};
