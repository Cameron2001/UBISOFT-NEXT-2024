#include "stdafx.h"
#include "Factory.h"

Entity Factory::createPlayer(Registry& Registry, vec2 pos, float radius, int segments, float hp, float shieldHp, float speed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown,  Entity id)
{
    if (id == NULL) id = Registry.createEntity();
    createCircle(Registry,pos,radius, segments,id);
    Registry.addComponent(id, CPlayer(speed));
    Registry.addComponent(id,CRigidbody(0.65,0.9));
    Registry.addComponent(id,CHealth(hp));
    Registry.addComponent(id,CTimer());
    Registry.addComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    Registry.addComponent(id, CShield(shieldHp));
    return id;
}

Entity Factory::createButton(Registry& Registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,
    Entity id)
{
    if (id == NULL) id = Registry.createEntity();
    createBox(Registry,pos,bounds,id);
    Registry.addComponent(id,CLabel(string,{bounds/-6.0f}));
    Registry.addComponent(id,CButton(type,bounds));
    return id;
}

Entity Factory::createEnemyTank(Registry& Registry, vec2 pos, vec2 bounds, float radius, float hp, float damage,
    float moveSpeed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown, Entity id)
{
    if(id == NULL) id = Registry.createEntity();
    createBox(Registry,pos,bounds,id);
    Registry.addComponent(id,CHealth(hp));
    Registry.addComponent(id,CDamage(damage));
    Registry.addComponent(id,CEnemyTank(moveSpeed));
    Registry.addComponent(id,CRigidbody(0.99,1.35));
    Registry.addComponent(id, CCircleCollider(radius,8,{-bounds.x-radius,0}));
    Registry.addComponent(id,CTimer());
    Registry.addComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    return id;
}

Entity Factory::createEnemyHoming(Registry& Registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed,
    Entity id)
{
    if(id == NULL) id = Registry.createEntity();
    createCircle(Registry,pos,radius, segments, id);
    Registry.addComponent(id, CHealth(hp));
    Registry.addComponent(id,CDamage(damage));
    Registry.addComponent(id,CEnemyHoming(moveSpeed));
    Registry.addComponent(id,CRigidbody(0.99,1.2));
    return id;
}

Entity Factory::createBox(Registry& Registry, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL) id = Registry.createEntity();
    Registry.addComponent(id, CTransform(pos));
    Registry.addComponent(id, CRender());
    Registry.addComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity Factory::createCircle(Registry& Registry, vec2 pos, float radius, int segments, Entity id)
{
    if (id == NULL) id = Registry.createEntity();
    Registry.addComponent(id, CTransform(pos));
    Registry.addComponent(id, CRender());
    Registry.addComponent(id,CCircleCollider(radius,segments));
    return id;
}

Entity Factory::createProjectile(Registry& Registry, vec2 pos, float radius, int segments, float force, float angle, float health,
    float damage, Entity id)
{
    if(id==NULL) id = Registry.createEntity();
    const vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    createCircle(Registry,pos+(dir*(radius+50.0f)),radius,segments,id);
    Registry.addComponent(id, CDamage(damage));
    Registry.addComponent(id, CHealth(health));
    Registry.addComponent(id,CRigidbody(0,1.7));
    Registry.getComponent<CRigidbody>(id).acceleration+=dir*force;
    return id;
}

Entity Factory::createWall(Registry& Registry, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id==NULL) id = Registry.createEntity();
    createBox(Registry,pos,bounds,id);
    Registry.addComponent(id, CHealth(hp));
    return id;
}

Entity Factory::createDamageEvent(Registry& Registry, Entity target, float damage, Entity id)
{
    if(id==NULL) id = Registry.createEntity();
    Registry.addComponent(id,CDamageEvent(target,damage));
    return id;
}

Entity Factory::createCollisionEvent(Registry& Registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal,
    Entity id)
{
    if(id==NULL) id = Registry.createEntity();
    Registry.addComponent(id,CCollisionEvent(entityA,entityB,mtv, normal));
    return id;
}

Entity Factory::createGameTimer(Registry& Registry, vec2 pos, Entity id)
{
    if(id==NULL) id = Registry.createEntity();
    Registry.addComponent(id,CTimer());
    Registry.addComponent(id, CLabel());
    Registry.addComponent(id,CTransform(pos));
    Registry.addComponent(id, CRender());
    return id;
}

Entity Factory::createWaveController(Registry& Registry, float waveCooldown, Entity id)
{
    if(id ==NULL) id = Registry.createEntity();
    Registry.addComponent(id,CTimer());
    Registry.addComponent(id, CWave(waveCooldown));
    return id;
}


Entity Factory::createLabel(Registry& Registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity id)
{
    if(id == NULL) id = Registry.createEntity();
    Registry.addComponent(id, CTransform(pos));
    Registry.addComponent(id,CRender(color));
    Registry.addComponent(id, CLabel(text,offset));
    return id;
}
