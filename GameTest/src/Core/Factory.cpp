#include "stdafx.h"
#include "Factory.h"

Entity Factory::CreatePlayer(Registry& Registry, vec2 pos, float radius, int segments, float hp, float shieldHp, float speed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown,  Entity id)
{
    if (id == NULL) id = Registry.CreateEntity();
    CreateCircle(Registry,pos,radius, segments,id);
    Registry.AddComponent(id, CPlayer(speed));
    Registry.AddComponent(id,CRigidbody(0.65,0.9));
    Registry.AddComponent(id,CHealth(hp));
    Registry.AddComponent(id,CTimer());
    Registry.AddComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    Registry.AddComponent(id, CShield(shieldHp));
    return id;
}

Entity Factory::CreateButton(Registry& Registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,
    Entity id)
{
    if (id == NULL) id = Registry.CreateEntity();
    CreateBox(Registry,pos,bounds,id);
    Registry.AddComponent(id,CLabel(string,{bounds/-2.0f}));
    Registry.AddComponent(id,CButton(type,bounds));
    return id;
}

Entity Factory::CreateEnemyTank(Registry& Registry, vec2 pos, vec2 bounds, float radius, float hp, float damage,
    float moveSpeed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown, Entity id)
{
    if(id == NULL) id = Registry.CreateEntity();
    CreateBox(Registry,pos,bounds,id);
    Registry.AddComponent(id,CHealth(hp));
    Registry.AddComponent(id,CDamage(damage));
    Registry.AddComponent(id,CEnemyTank(moveSpeed));
    Registry.AddComponent(id,CRigidbody(0.99,1.35));
    Registry.AddComponent(id, CCircleCollider(radius,8,{-bounds.x-radius,0}));
    Registry.AddComponent(id,CTimer());
    Registry.AddComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    return id;
}

Entity Factory::CreateEnemyHoming(Registry& Registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed,
    Entity id)
{
    if(id == NULL) id = Registry.CreateEntity();
    CreateCircle(Registry,pos,radius, segments, id);
    Registry.AddComponent(id, CHealth(hp));
    Registry.AddComponent(id,CDamage(damage));
    Registry.AddComponent(id,CEnemyHoming(moveSpeed));
    Registry.AddComponent(id,CRigidbody(0.99,1.2));
    return id;
}

Entity Factory::CreateBox(Registry& Registry, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id, CTransform(pos));
    Registry.AddComponent(id, CRender());
    Registry.AddComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity Factory::CreateCircle(Registry& Registry, vec2 pos, float radius, int segments, Entity id)
{
    if (id == NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id, CTransform(pos));
    Registry.AddComponent(id, CRender());
    Registry.AddComponent(id,CCircleCollider(radius,segments));
    return id;
}

Entity Factory::CreateProjectile(Registry& Registry, vec2 pos, float radius, int segments, float force, float angle, float health,
    float damage, Entity id)
{
    if(id==NULL) id = Registry.CreateEntity();
    const vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    CreateCircle(Registry,pos+(dir*(radius+50.0f)),radius,segments,id);
    Registry.AddComponent(id, CDamage(damage));
    Registry.AddComponent(id, CHealth(health));
    Registry.AddComponent(id,CRigidbody(0,1.7));
    Registry.GetComponent<CRigidbody>(id)->acceleration+=dir*force;
    return id;
}

Entity Factory::CreateWall(Registry& Registry, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id==NULL) id = Registry.CreateEntity();
    CreateBox(Registry,pos,bounds,id);
    Registry.AddComponent(id, CHealth(hp));
    return id;
}

Entity Factory::CreateDamageEvent(Registry& Registry, Entity target, float damage, Entity id)
{
    if(id==NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id,CDamageEvent(target,damage));
    return id;
}

Entity Factory::CreateCollisionEvent(Registry& Registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal,
    Entity id)
{
    if(id==NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id,CCollisionEvent(entityA,entityB,mtv, normal));
    return id;
}

Entity Factory::CreateGameTimer(Registry& Registry, vec2 pos, Entity id)
{
    if(id==NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id,CTimer());
    Registry.AddComponent(id, CLabel());
    Registry.AddComponent(id,CTransform(pos));
    Registry.AddComponent(id, CRender());
    return id;
}

Entity Factory::CreateWaveController(Registry& Registry, float waveCooldown, Entity id)
{
    if(id ==NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id,CTimer());
    Registry.AddComponent(id, CWave(waveCooldown));
    return id;
}


Entity Factory::CreateLabel(Registry& Registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity id)
{
    if(id == NULL) id = Registry.CreateEntity();
    Registry.AddComponent(id, CTransform(pos));
    Registry.AddComponent(id,CRender(color));
    Registry.AddComponent(id, CLabel(text,offset));
    return id;
}
