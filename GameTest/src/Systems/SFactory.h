﻿#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"

class SFactory : public ISystem
{
public:
    Entity CreatePlayer(Scene& scene, vec2 pos, float radius, Entity id = NULL);
    Entity CreateButton(Scene& scene, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity id = NULL);
    Entity CreateEnemyTank(Scene& scene, vec2 pos, vec2 bounds, float radius, float hp, float damage, Entity id = NULL);
    Entity CreateBox(Scene& scene, vec2 pos, vec2 bounds,  vec3 InColor = {1.0,1.0,1.0}, Entity id = NULL);
    Entity CreateCircle(Scene& scene, vec2 pos, float radius,  vec3 InColor = {1.0,1.0,1.0}, Entity id = NULL);
    Entity CreateProjectile(Scene& scene,vec2 pos, float radius, float force, float angle, float health=1, float damage=50, Entity id = NULL);
    Entity CreateWall(Scene& scene, vec2 pos, vec2 bounds, float hp, Entity id = NULL);
    Entity CreateDamageEvent(Scene& scene, Entity target, float damage, Entity id = NULL);
    Entity CreateCollisionEvent(Scene& scene, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id = NULL);
    Entity CreateScoreTimer(Scene& scene, Entity id = NULL);
};
