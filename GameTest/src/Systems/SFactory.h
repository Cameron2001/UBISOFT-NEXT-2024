#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"

class SFactory : public ISystem
{
public:
    Entity CreatePlayer(Scene& scene, vec2 pos, float radius, Entity id = NULL);
    Entity CreateButton(Scene& scene, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity id = NULL);
    Entity CreateEnemy(Scene& scene, vec2 pos, vec2 bounds, float hp, float damage, Entity id = NULL);
    Entity CreateBox(Scene& scene, vec2 pos, vec2 bounds, Entity id = NULL);
    Entity CreateCircle(Scene& scene, vec2 pos, float radius, Entity id = NULL);
    Entity CreateProjectile(Scene& scene,vec2 pos, float radius, float force, float angle, float health=1, float damage=50, Entity id = NULL);
    Entity CreateDamageEvent(Scene& scene, Entity target, float damage, Entity id = NULL);
    Entity CreateCollisionEvent(Scene& scene, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id = NULL);
    
};
