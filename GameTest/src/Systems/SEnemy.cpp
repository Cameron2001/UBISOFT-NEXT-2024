#include "stdafx.h"
#include "SEnemy.h"

#include "../../app/AppSettings.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"

void SEnemy::update(Registry& registry, float dt)
{
    const auto waveController = registry.getEntities<CWave>()[0];
    CTimer& timer = registry.getComponent<CTimer>(waveController);
    const CWave& wave = registry.getComponent<CWave>(waveController);
    if(timer.timer>wave.waveCooldown)
    {
        timer.timer = 0.0f;
        spawnWave(registry, wave.difficultyMultiplier);
    }
    updateTanks(registry,dt);
    updateHoming(registry,dt);
}

void SEnemy::updateTanks(Registry& registry, float dt)
{
    auto playerPos = registry.getComponent<CTransform>(registry.getEntities<CPlayer>()[0]).pos;
    for (const auto element : registry.getEntities<CEnemyTank>())
    {
        CRigidbody& rb = registry.getComponent<CRigidbody>(element);
        CEnemyTank& tank = registry.getComponent<CEnemyTank>(element);
        CTransform& transform = registry.getComponent<CTransform>(element);
        CCircleCollider& circle = registry.getComponent<CCircleCollider>(element);
        CArm& arm = registry.getComponent<CArm>(element);

        const vec2 armStart = transform.pos+circle.offset;
        arm.rotation =atan2f(playerPos.y-armStart.y,playerPos.x-armStart.x);
        if(arm.rotation*Utils::Rad2Deg < 0) arm.rotation+=Utils::Deg2Rad*360;
        arm.rotation = Utils::Clamp(arm.rotation,75*Utils::Deg2Rad, 255*Utils::Deg2Rad);
        
        rb.acceleration.x-=tank.moveSpeed;
        
    }
}

void SEnemy::updateHoming(Registry& registry, float dt)
{
    for (auto element : registry.getEntities<CEnemyHoming>())
    {
        CEnemyHoming& homingComp = registry.getComponent<CEnemyHoming>(element);
        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(element);
        CTransform& transform = registry.getComponent<CTransform>(element);
        const CTransform& playerTransform = registry.getComponent<CTransform>(registry.getEntities<CPlayer>()[0]);
        vec2 diff = {playerTransform.pos.x-transform.pos.x,playerTransform.pos.y-transform.pos.y};
        rigidbody.acceleration+= Utils::Normalize(diff)*homingComp.moveSpeed;
        
    }
}

void SEnemy::spawnWave(Registry& registry, float difficultyMultiplier)
{
    float multiplier = FRAND_RANGE(1.0f, 1.5f)*difficultyMultiplier;
    Factory::createEnemyTank(registry, {800*difficultyMultiplier,300}, {20,8},10,50*multiplier, 10.0f*multiplier, 200,15000*multiplier, 25 *multiplier, 20*multiplier, 10.0f*multiplier,30.0f,5.0f*multiplier);
    Factory::createEnemyTank(registry, {900*difficultyMultiplier,500}, {30,10},15,75*multiplier, 10.0f*multiplier, 150,20000*multiplier, 30 *multiplier, 30*multiplier, 10.0f*multiplier,40.0f, 6.0*multiplier);
    Factory::createEnemyHoming(registry, {1000*difficultyMultiplier,400},20*multiplier, 6,20*multiplier, 10*multiplier,600*multiplier);
}

