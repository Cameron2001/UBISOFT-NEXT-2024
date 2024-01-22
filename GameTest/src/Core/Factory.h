//------------------------------------------------------------------------
// Factory.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Components/Components.h"
#include "../Core/Scene.h"
//------------------------------------------------------------------------
class factory
{
public:
    static Entity createPlayer(Registry& registry, vec2 pos, float radius, int segments = 10, float health = 100.0f,  float speed = 1000.0f, float projForce = 20000.0f, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity ID = NULL);
    static Entity createButton(Registry& registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity ID = NULL);
    static Entity createEnemyTank(Registry& registry, vec2 pos, vec2 bounds, float radius, float hp, float damage, float moveSpeed = 50.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity ID = NULL);
    static Entity createEnemyHoming(Registry& registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed, Entity ID = NULL);
    static Entity createBox(Registry& registry, vec2 pos, vec2 bounds, Entity ID = NULL);
    static Entity createCircle(Registry& registry, vec2 pos, float radius, int segments = 10, Entity ID = NULL);
    static Entity createProjectile(Registry& registry,vec2 pos, float radius, float offset, int segments, float force, float angle, float health=20.0f, float damage=50.0f, Entity ID = NULL);
    static Entity createWall(Registry& registry, vec2 pos, vec2 bounds, float hp, Entity ID = NULL);
    static Entity createDamageEvent(Registry& registry, Entity target, float damage, Entity ID = NULL);
    static Entity createCollisionEvent(Registry& registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity ID = NULL);
    static Entity createGameTimer(Registry& registry, vec2 pos, Entity ID = NULL);
    static Entity createWaveController(Registry& registry, float waveCooldown, Entity ID = NULL);
    static Entity createLabel(Registry& registry, std::string text, vec2 pos, vec2 offset = {0.0f,0.0f}, vec3 color = {1.0f,1.0f,1.0f}, Entity ID = NULL);
    
};
