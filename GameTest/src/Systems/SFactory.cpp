﻿#include "stdafx.h"
#include "SFactory.h"

#include "../Util/Utils.h"

Entity SFactory::CreatePlayer(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    //CreateBox(scene,pos,{25,25},id);
    CreateCircle(scene,pos,radius,id);
    scene.reg.AddComponent(id, CPlayer(1000));
    scene.reg.AddComponent(id,CRigidbody());
    scene.reg.AddComponent(id,CHealth(100));
    scene.reg.AddComponent(id,CTimer());
    scene.reg.AddComponent(id,CLabel("Player"));
    scene.reg.AddComponent(id, CArm(50.0f));
    return id;
}

Entity SFactory::CreateButton(Scene& scene, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id,CLabel(string,{bounds/-2.0f}));
    scene.reg.AddComponent(id,CButton(type,bounds));
    return id;
}


Entity SFactory::CreateEnemyTank(Scene& scene, vec2 pos, vec2 bounds, float radius, float hp, float damage,float moveSpeed, float projForce, float projHealth, float projDmg, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id,CHealth(hp));
    scene.reg.AddComponent(id,CDamage(damage));
    scene.reg.AddComponent(id,CEnemyTank(projDmg, projForce,projHealth,moveSpeed));
    scene.reg.AddComponent(id,CRigidbody(0.99,1.35));
    scene.reg.AddComponent(id, CCircleCollider(radius,{-bounds.x-radius,0}));
    scene.reg.AddComponent(id,CTimer());
    scene.reg.AddComponent(id, CArm(30.0f));
    return id;
}

Entity SFactory::CreateEnemyHoming(Scene& scene, vec2 pos, float radius, float hp, float damage, float moveSpeed, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    CreateCircle(scene,pos,radius,id);
    scene.reg.AddComponent(id, CHealth(hp));
    scene.reg.AddComponent(id,CDamage(damage));
    scene.reg.AddComponent(id,CEnemyHoming(moveSpeed));
    scene.reg.AddComponent(id,CRigidbody(0.99,1.2));
    return id;
}

Entity SFactory::CreateBox(Scene& scene, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity SFactory::CreateCircle(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender());
    scene.reg.AddComponent(id,CCircleCollider(radius));
    return id;
}


Entity SFactory::CreateProjectile(Scene& scene, vec2 pos, float radius, float force, float angle, float health, float damage, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    const vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    CreateCircle(scene,pos+(dir*(radius+50.0f)),radius,id);
    scene.reg.AddComponent(id, CDamage(damage));
    scene.reg.AddComponent(id, CHealth(health));
    scene.reg.AddComponent(id,CRigidbody(0,1.7));
    scene.reg.GetComponent<CRigidbody>(id)->acceleration+=dir*force;
    return id;
    
}

Entity SFactory::CreateWall(Scene& scene, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,id);
    scene.reg.AddComponent(id, CHealth(hp));
    return id;
}

Entity SFactory::CreateDamageEvent(Scene& scene, Entity target, float damage, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CDamageEvent(target,damage));
    return id;
}



Entity SFactory::CreateCollisionEvent(Scene& scene, Entity entityA, Entity entityB, vec2 mtv, vec2 normal, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CCollisionEvent(entityA,entityB,mtv, normal));
    return id;
}

Entity SFactory::CreateGameTimer(Scene& scene, vec2 pos, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CTimer());
    scene.reg.AddComponent(id, CLabel());
    scene.reg.AddComponent(id,CTransform(pos));
    scene.reg.AddComponent(id, CRender());
    return id;
}

Entity SFactory::CreateWaveController(Scene& scene, float waveCooldown, Entity id)
{
    if(id ==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CTimer());
    scene.reg.AddComponent(id, CWave(waveCooldown));
    return id;
}

Entity SFactory::CreatePlayerShield(Scene& scene, vec2 pos, float radius, float hp, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CShield());
    scene.reg.AddComponent(id, CHealth(hp));
    scene.reg.AddComponent(id, CTransform());
    scene.reg.AddComponent(id, CRender());
    return id;
}


