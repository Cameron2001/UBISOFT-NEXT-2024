#include "stdafx.h"
#include "SFactory.h"

#include "../Util/Utils.h"

Entity SFactory::CreatePlayer(Scene& scene, vec2 pos, float radius, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    //CreateBox(scene,pos,{25,25},id);
    CreateCircle(scene,pos,radius,{0.3,0.3,0.8},id);
    scene.reg.AddComponent(id, CPlayer(10,1000));
    scene.reg.AddComponent(id,CRigidbody());
    scene.reg.AddComponent(id,CHealth(100));
    scene.reg.AddComponent(id,CTimer());
    return id;
}

Entity SFactory::CreateButton(Scene& scene, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,{1.0,1.0,1.0},id);
    scene.reg.AddComponent(id,CLabel(string,{bounds/-2.0f}));
    scene.reg.AddComponent(id,CButton(type,bounds));
    return id;
}


Entity SFactory::CreateEnemyTank(Scene& scene, vec2 pos, vec2 bounds, float radius, float hp, float damage, Entity id)
{
    if(id == NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds, {0.5,0.8,0.5},id);
    scene.reg.AddComponent(id,CHealth(hp));
    scene.reg.AddComponent(id,CDamage(damage));
    scene.reg.AddComponent(id,CEnemyTank());
    scene.reg.AddComponent(id,CRigidbody(0.99));
    scene.reg.AddComponent(id, CCircleCollider(radius,{-bounds.x-radius,0}));
    scene.reg.AddComponent(id,CTimer());
    return id;
}

Entity SFactory::CreateBox(Scene& scene, vec2 pos, vec2 bounds, vec3 InColor,  Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender(InColor));
    scene.reg.AddComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity SFactory::CreateCircle(Scene& scene, vec2 pos, float radius, vec3 InColor, Entity id)
{
    if (id == NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id, CTransform(pos));
    scene.reg.AddComponent(id, CRender(InColor));
    scene.reg.AddComponent(id,CCircleCollider(radius));
    return id;
}


Entity SFactory::CreateProjectile(Scene& scene, vec2 pos, float radius, float force, float angle, float health, float damage, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    CreateCircle(scene,pos+(dir*(radius+50.0f)),radius,{1.0,1.0,1.0},id);
    scene.reg.AddComponent(id, CDamage(damage));
    scene.reg.AddComponent(id, CHealth(health));
    scene.reg.AddComponent(id,CRigidbody(0,1.75));
    scene.reg.GetComponent<CRigidbody>(id)->acceleration+=dir*force;
    return id;
    
}

Entity SFactory::CreateWall(Scene& scene, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    CreateBox(scene,pos,bounds,{1.0,1.0,1.0},id);
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

Entity SFactory::CreateScoreTimer(Scene& scene, Entity id)
{
    if(id==NULL)
        id = scene.reg.CreateEntity();
    scene.reg.AddComponent(id,CTimer());
    scene.reg.AddComponent(id,CScoreKeeper());
    return id;
}


