//------------------------------------------------------------------------
// Factory.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Factory.h"
//------------------------------------------------------------------------

Entity factory::createPlayer(Registry& registry, const vec2 pos, const float radius, const int segments,
                             const float health, const float speed,
                             const float projForce, const float projHealth, const float projDmg, const float projRadius,
                             const float armLength,
                             const float coolDown, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createCircle(registry, pos, radius, segments, ID);
    registry.addComponent(ID, CPlayer(speed));
    registry.addComponent(ID, CRigidbody(0.65, 0.9));
    registry.addComponent(ID, CHealth(health));
    registry.addComponent(ID, CTimer());
    registry.addComponent(ID, CArm(armLength, projForce, projHealth, projDmg, projRadius, coolDown));
    return ID;
}

Entity factory::createButton(Registry& registry, const vec2 pos, const vec2 bounds, const CButton::ButtonTypes type,
                             const char* string,
                             Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createBox(registry, pos, bounds, ID);
    registry.addComponent(ID, CLabel(string, {bounds / -6.0f}));
    registry.addComponent(ID, CButton(type, bounds));
    return ID;
}

Entity factory::createEnemyTank(Registry& registry, const vec2 pos, const vec2 bounds, const float radius,
                                const float health, const float damage,
                                const float moveSpeed, const float projForce, const float projHealth,
                                const float projDmg, const float projRadius,
                                const float armLength, const float coolDown, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createBox(registry, pos, bounds, ID);
    registry.addComponent(ID, CHealth(health));
    registry.addComponent(ID, CDamage(damage));
    registry.addComponent(ID, CEnemyTank(moveSpeed));
    registry.addComponent(ID, CRigidbody(0.99, 1.35));
    registry.addComponent(ID, CCircleCollider(radius, 8, {-bounds.x - radius, 0}));
    registry.addComponent(ID, CTimer());
    registry.addComponent(ID, CArm(armLength, projForce, projHealth, projDmg, projRadius, coolDown));
    return ID;
}

Entity factory::createEnemyHoming(Registry& registry, const vec2 pos, const float radius, const int segments,
                                  const float health, const float damage,
                                  const float moveSpeed,
                                  Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createCircle(registry, pos, radius, segments, ID);
    registry.addComponent(ID, CHealth(health));
    registry.addComponent(ID, CDamage(damage));
    registry.addComponent(ID, CEnemyHoming(moveSpeed));
    registry.addComponent(ID, CRigidbody(0.99, 1.2));
    return ID;
}

Entity factory::createBox(Registry& registry, const vec2 pos, const vec2 bounds, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender());
    registry.addComponent(ID, CBoxCollider(bounds));
    return ID;
}

Entity factory::createCircle(Registry& registry, const vec2 pos, const float radius, const int segments, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender());
    registry.addComponent(ID, CCircleCollider(radius, segments));
    return ID;
}

Entity factory::createProjectile(Registry& registry, const vec2 pos, const float radius, const float offset,
                                 const int segments, const float force,
                                 const float angle, const float health,
                                 const float damage, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    const vec2 dir = {cos(angle), sin(angle)};
    createCircle(registry, pos + dir * (radius + offset + 1), radius, segments, ID);
    registry.addComponent(ID, CDamage(damage));
    registry.addComponent(ID, CHealth(health));
    registry.addComponent(ID, CRigidbody(0, 1.7));
    registry.getComponent<CRigidbody>(ID).acceleration += dir * force;
    return ID;
}

Entity factory::createWall(Registry& registry, const vec2 pos, const vec2 bounds, const float health, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    createBox(registry, pos, bounds, ID);
    registry.addComponent(ID, CHealth(health));
    return ID;
}

Entity factory::createDamageEvent(Registry& registry, const Entity target, const float damage, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CDamageEvent(target, damage));
    return ID;
}

Entity factory::createCollisionEvent(Registry& registry, const Entity entityA, const Entity entityB, const vec2 mtv,
                                     const vec2 normal,
                                     Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CCollisionEvent(entityA, entityB, mtv, normal));
    return ID;
}

Entity factory::createGameTimer(Registry& registry, const vec2 pos, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTimer());
    registry.addComponent(ID, CLabel());
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender());
    return ID;
}

Entity factory::createWaveController(Registry& registry, const float waveCooldown, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTimer());
    registry.addComponent(ID, CWave(waveCooldown));
    return ID;
}


Entity factory::createLabel(Registry& registry, const std::string& text, const vec2 pos, const vec2 offset,
                            const vec3 color, Entity ID)
{
    if (ID == NULL) ID = registry.createEntity();
    registry.addComponent(ID, CTransform(pos));
    registry.addComponent(ID, CRender(color));
    registry.addComponent(ID, CLabel(text, offset));
    return ID;
}
