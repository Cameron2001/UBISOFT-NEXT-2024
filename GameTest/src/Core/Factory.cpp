#include "stdafx.h"
#include "Factory.h"

Entity Factory::createPlayer(Registry& registry, vec2 pos, float radius, int segments, float hp, float shieldHp, float speed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown,  Entity id)
{
    if (id == NULL) id = registry.createEntity();
    createCircle(registry,pos,radius, segments,id);
    registry.addComponent(id, CPlayer(speed));
    registry.addComponent(id,CRigidbody(0.65,0.9));
    registry.addComponent(id,CHealth(hp));
    registry.addComponent(id,CTimer());
    registry.addComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    registry.addComponent(id, CShield(shieldHp));
    return id;
}

Entity Factory::createButton(Registry& registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,
    Entity id)
{
    if (id == NULL) id = registry.createEntity();
    createBox(registry,pos,bounds,id);
    registry.addComponent(id,CLabel(string,{bounds/-6.0f}));
    registry.addComponent(id,CButton(type,bounds));
    return id;
}

Entity Factory::createEnemyTank(Registry& registry, vec2 pos, vec2 bounds, float radius, float hp, float damage,
    float moveSpeed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown, Entity id)
{
    if(id == NULL) id = registry.createEntity();
    createBox(registry,pos,bounds,id);
    registry.addComponent(id,CHealth(hp));
    registry.addComponent(id,CDamage(damage));
    registry.addComponent(id,CEnemyTank(moveSpeed));
    registry.addComponent(id,CRigidbody(0.99,1.35));
    registry.addComponent(id, CCircleCollider(radius,8,{-bounds.x-radius,0}));
    registry.addComponent(id,CTimer());
    registry.addComponent(id, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    return id;
}

Entity Factory::createEnemyHoming(Registry& registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed,
    Entity id)
{
    if(id == NULL) id = registry.createEntity();
    createCircle(registry,pos,radius, segments, id);
    registry.addComponent(id, CHealth(hp));
    registry.addComponent(id,CDamage(damage));
    registry.addComponent(id,CEnemyHoming(moveSpeed));
    registry.addComponent(id,CRigidbody(0.99,1.2));
    return id;
}

Entity Factory::createBox(Registry& registry, vec2 pos, vec2 bounds, Entity id)
{
    if (id == NULL) id = registry.createEntity();
    registry.addComponent(id, CTransform(pos));
    registry.addComponent(id, CRender());
    registry.addComponent(id,CBoxCollider(bounds));
    return  id;
}

Entity Factory::createCircle(Registry& registry, vec2 pos, float radius, int segments, Entity id)
{
    if (id == NULL) id = registry.createEntity();
    registry.addComponent(id, CTransform(pos));
    registry.addComponent(id, CRender());
    registry.addComponent(id,CCircleCollider(radius,segments));
    return id;
}

Entity Factory::createProjectile(Registry& registry, vec2 pos, float radius, int segments, float force, float angle, float health,
    float damage, Entity id)
{
    if(id==NULL) id = registry.createEntity();
    const vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    createCircle(registry,pos+(dir*(radius+50.0f)),radius,segments,id);
    registry.addComponent(id, CDamage(damage));
    registry.addComponent(id, CHealth(health));
    registry.addComponent(id,CRigidbody(0,1.7));
    registry.getComponent<CRigidbody>(id).acceleration+=dir*force;
    return id;
}

Entity Factory::createWall(Registry& registry, vec2 pos, vec2 bounds, float hp, Entity id)
{
    if(id==NULL) id = registry.createEntity();
    createBox(registry,pos,bounds,id);
    registry.addComponent(id, CHealth(hp));
    return id;
}

Entity Factory::createDamageEvent(Registry& registry, Entity target, float damage, Entity id)
{
    if(id==NULL) id = registry.createEntity();
    registry.addComponent(id,CDamageEvent(target,damage));
    return id;
}

Entity Factory::createCollisionEvent(Registry& registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal,
    Entity id)
{
    if(id==NULL) id = registry.createEntity();
    registry.addComponent(id,CCollisionEvent(entityA,entityB,mtv, normal));
    return id;
}

Entity Factory::createGameTimer(Registry& registry, vec2 pos, Entity id)
{
    if(id==NULL) id = registry.createEntity();
    registry.addComponent(id,CTimer());
    registry.addComponent(id, CLabel());
    registry.addComponent(id,CTransform(pos));
    registry.addComponent(id, CRender());
    return id;
}

Entity Factory::createWaveController(Registry& registry, float waveCooldown, Entity id)
{
    if(id ==NULL) id = registry.createEntity();
    registry.addComponent(id,CTimer());
    registry.addComponent(id, CWave(waveCooldown));
    return id;
}


Entity Factory::createLabel(Registry& registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity id)
{
    if(id == NULL) id = registry.createEntity();
    registry.addComponent(id, CTransform(pos));
    registry.addComponent(id,CRender(color));
    registry.addComponent(id, CLabel(text,offset));
    return id;
}
