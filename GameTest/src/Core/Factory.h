#pragma once
#include "../Components/Components.h"
#include "../Core/Scene.h"
class Factory
{
public:
    static Entity createPlayer(Registry& Registry, vec2 pos, float radius, int segments = 10, float health = 100.0f, float shieldHealth = 50.0f,  float speed = 1000.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity id = NULL);
    static Entity createButton(Registry& Registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity id = NULL);
    static Entity createEnemyTank(Registry& Registry, vec2 pos, vec2 bounds, float radius, float hp, float damage, float moveSpeed = 50.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, float projRadius = 20.0f, float armLength = 40.0f, float coolDown = 4.0f, Entity id = NULL);
    static Entity createEnemyHoming(Registry& Registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed, Entity id = NULL);
    static Entity createBox(Registry& Registry, vec2 pos, vec2 bounds, Entity id = NULL);
    static Entity createCircle(Registry& Registry, vec2 pos, float radius, int segments = 10, Entity id = NULL);
    static Entity createProjectile(Registry& Registry,vec2 pos, float radius, int segments, float force, float angle, float health=1, float damage=50, Entity id = NULL);
    static Entity createWall(Registry& Registry, vec2 pos, vec2 bounds, float hp, Entity id = NULL);
    static Entity createDamageEvent(Registry& Registry, Entity target, float damage, Entity id = NULL);
    static Entity createCollisionEvent(Registry& Registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id = NULL);
    static Entity createGameTimer(Registry& Registry, vec2 pos, Entity id = NULL);
    static Entity createWaveController(Registry& Registry, float waveCooldown, Entity id = NULL);
    static Entity createLabel(Registry& Registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity id = NULL);
private:
    
};
