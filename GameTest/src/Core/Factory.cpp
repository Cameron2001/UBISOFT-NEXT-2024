//------------------------------------------------------------------------
// Factory.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Factory.h"
//------------------------------------------------------------------------

Entity factory::createPlayer(Registry& registry, vec2 pos, float radius, int segments, float hp, float shieldHp, float speed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown,  Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createCircle(registry,pos,radius, segments,ID);
    registry.addComponent(ID, CPlayer(speed));
    registry.addComponent(ID,CRigidbody(0.65,0.9));
    registry.addComponent(ID,CHealth(hp));
    registry.addComponent(ID,CTimer());
    registry.addComponent(ID, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    registry.addComponent(ID, CShield(shieldHp));
    return ID;
}

Entity factory::createButton(Registry& registry, vec2 pos, vec2 bounds, CButton::ButtonTypes type, const char* string,
    Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createBox(registry,pos,bounds,ID);
    registry.addComponent(ID,CLabel(string,{bounds/-6.0f}));
    registry.addComponent(ID,CButton(type,bounds));
    return ID;
}

Entity factory::createEnemyTank(Registry& registry, vec2 pos, vec2 bounds, float radius, float hp, float damage,
    float moveSpeed, float projForce, float projHealth, float projDmg, float projRadius, float armLength, float coolDown, Entity ID)
{
    if(ID == NULL) ID = registry.createEntity();
    createBox(registry,pos,bounds,ID);
    registry.addComponent(ID,CHealth(hp));
    registry.addComponent(ID,CDamage(damage));
    registry.addComponent(ID,CEnemyTank(moveSpeed));
    registry.addComponent(ID,CRigidbody(0.99,1.35));
    registry.addComponent(ID, CCircleCollider(radius,8,{-bounds.x-radius,0}));
    registry.addComponent(ID,CTimer());
    registry.addComponent(ID, CArm(armLength,projForce, projHealth,projDmg, projRadius, coolDown));
    return ID;
}

Entity factory::createEnemyHoming(Registry& registry, vec2 pos, float radius, int segments, float hp, float damage, float moveSpeed,
    Entity ID)
{
    if(ID == NULL) ID = registry.createEntity();
    createCircle(registry,pos,radius, segments, ID);
    registry.addComponent(ID, CHealth(hp));
    registry.addComponent(ID,CDamage(damage));
    registry.addComponent(ID,CEnemyHoming(moveSpeed));
    registry.addComponent(ID,CRigidbody(0.99,1.2));
    return ID;
}

Entity factory::createBox(Registry& registry, vec2 pos, vec2 bounds, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender());
    registry.addComponent(ID,CBoxCollider(bounds));
    return  ID;
}

Entity factory::createCircle(Registry& registry, vec2 pos, float radius, int segments, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender());
    registry.addComponent(ID,CCircleCollider(radius,segments));
    return ID;
}

Entity factory::createProjectile(Registry& registry, vec2 pos, float radius, int segments, float force, float angle, float health,
    float damage, Entity ID)
{
    if(ID==NULL) ID = registry.createEntity();
    const vec2 dir = {cos(angle),sin(angle)};
    //the 50 is player radius
    createCircle(registry,pos+(dir*(radius+50.0f)),radius,segments,ID);
    registry.addComponent(ID, CDamage(damage));
    registry.addComponent(ID, CHealth(health));
    registry.addComponent(ID,CRigidbody(0,1.7));
    registry.getComponent<CRigidbody>(ID).acceleration+=dir*force;
    return ID;
}

Entity factory::createWall(Registry& registry, vec2 pos, vec2 bounds, float hp, Entity ID)
{
    if(ID==NULL) ID = registry.createEntity();
    createBox(registry,pos,bounds,ID);
    registry.addComponent(ID, CHealth(hp));
    return ID;
}

Entity factory::createDamageEvent(Registry& registry, Entity target, float damage, Entity ID)
{
    if(ID==NULL) ID = registry.createEntity();
    registry.addComponent(ID,CDamageEvent(target,damage));
    return ID;
}

Entity factory::createCollisionEvent(Registry& registry, Entity entityA, Entity entityB, vec2 mtv, vec2 normal,
    Entity ID)
{
    if(ID==NULL) ID = registry.createEntity();
    registry.addComponent(ID,CCollisionEvent(entityA,entityB,mtv, normal));
    return ID;
}

Entity factory::createGameTimer(Registry& registry, vec2 pos, Entity ID)
{
    if(ID==NULL) ID = registry.createEntity();
    registry.addComponent(ID,CTimer());
    registry.addComponent(ID, CLabel());
    registry.addComponent(ID,CTransform(pos));
    registry.addComponent(ID, CRender());
    return ID;
}

Entity factory::createWaveController(Registry& registry, float waveCooldown, Entity ID)
{
    if(ID ==NULL) ID = registry.createEntity();
    registry.addComponent(ID,CTimer());
    registry.addComponent(ID, CWave(waveCooldown));
    return ID;
}


Entity factory::createLabel(Registry& registry, std::string text, vec2 pos, vec2 offset, vec3 color, Entity ID)
{
    if(ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID,CRender(color));
    registry.addComponent(ID, CLabel(text,offset));
    return ID;
}
