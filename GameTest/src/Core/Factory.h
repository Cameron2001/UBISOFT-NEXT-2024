#pragma once
#include "../Components/Components.h"
#include "../Core/Scene.h"
struct Factory
{
    static Entity createPlayer(Registry& registry, vec2 pos, float radius, int segments = 10, float health = 100.0f, float shieldHealth = 50.0f,  float speed = 1000.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity id = NULL);
    static Entity createButton(Registry& registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity id = NULL);
    static Entity createEnemyTank(Registry& registry, vec2 pos, vec2 bounds, float radius, float hp, float damage, float moveSpeed = 50.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity id = NULL);
    static Entity createEnemyHoming(Registry& registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed, Entity id = NULL);
    static Entity createBox(Registry& registry, vec2 pos, vec2 bounds, Entity id = NULL);
    static Entity createCircle(Registry& registry, vec2 pos, float radius, int segments = 10, Entity id = NULL);
    static Entity createProjectile(Registry& registry,vec2 pos, float radius, int segments, float force, float angle, float health=1, float damage=50, Entity id = NULL);
    static Entity createWall(Registry& registry, vec2 pos, vec2 bounds, float hp, Entity id = NULL);
    static Entity createDamageEvent(Registry& registry, Entity target, float damage, Entity id = NULL);
    static Entity createCollisionEvent(Registry& registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id = NULL);
    static Entity createGameTimer(Registry& registry, vec2 pos, Entity id = NULL);
    static Entity createWaveController(Registry& registry, float waveCooldown, Entity id = NULL);
    static Entity createLabel(Registry& registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity id = NULL);
    
};
