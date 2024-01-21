﻿#pragma once
#include "../Components/Components.h"
#include "../Core/Scene.h"
class Factory
{
public:
    static Entity CreatePlayer(Registry& Registry, vec2 pos, float radius, Entity id = NULL);
    static Entity CreateButton(Registry& Registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string = "Button Label", Entity id = NULL);
    static Entity CreateEnemyTank(Registry& Registry, vec2 pos, vec2 bounds, float radius, float hp, float damage, float moveSpeed = 50.0f, float projForce = 20000, float projHealth = 100.0f, float projDmg = 50.0f, Entity id = NULL);
    static Entity CreateEnemyHoming(Registry& Registry, vec2 pos, float radius, float hp, float damage, float moveSpeed, Entity id = NULL);
    static Entity CreateBox(Registry& Registry, vec2 pos, vec2 bounds, Entity id = NULL);
    static Entity CreateCircle(Registry& Registry, vec2 pos, float radius, Entity id = NULL);
    static Entity CreateProjectile(Registry& Registry,vec2 pos, float radius, float force, float angle, float health=1, float damage=50, Entity id = NULL);
    static Entity CreateWall(Registry& Registry, vec2 pos, vec2 bounds, float hp, Entity id = NULL);
    static Entity CreateDamageEvent(Registry& Registry, Entity target, float damage, Entity id = NULL);
    static Entity CreateCollisionEvent(Registry& Registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id = NULL);
    static Entity CreateGameTimer(Registry& Registry, vec2 pos, Entity id = NULL);
    static Entity CreateWaveController(Registry& Registry, float waveCooldown, Entity id = NULL);
    static Entity CreatePlayerShield (Registry& Registry, vec2 pos, float radius, float hp, Entity id = NULL);
private:
    Factory();
    ~Factory();
    
};