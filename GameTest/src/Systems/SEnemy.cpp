//------------------------------------------------------------------------
// SEnemy.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "SEnemy.h"
//------------------------------------------------------------------------
#include "../../app/AppSettings.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"
//------------------------------------------------------------------------

void SEnemy::update(Registry& registry, float dt)
{
    const Entity waveController = registry.getEntities<CWave>()[0];
    const CWave& wave = registry.getComponent<CWave>(waveController);
    CTimer& timer = registry.getComponent<CTimer>(waveController);
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
    const auto playerPos = registry.getComponent<CTransform>(registry.getEntities<CPlayer>()[0]).pos;
    for (const Entity ID : registry.getEntities<CEnemyTank>())
    {
        const CEnemyTank& tank = registry.getComponent<CEnemyTank>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        const CCircleCollider& circle = registry.getComponent<CCircleCollider>(ID);
        
        CRigidbody& rb = registry.getComponent<CRigidbody>(ID);
        CArm& arm = registry.getComponent<CArm>(ID);

        const vec2 armStart = transform.pos+circle.offset;
        arm.rotation =atan2f(playerPos.y-armStart.y,playerPos.x-armStart.x);
        if(arm.rotation*utils::rad2Deg < 0.0f) arm.rotation+=utils::deg2Rad*360.0f;
        arm.rotation = utils::clamp(arm.rotation,75.0f*utils::deg2Rad, 255.0f*utils::deg2Rad);
        
        rb.acceleration.x-=tank.moveSpeed;
        
    }
}

void SEnemy::updateHoming(Registry& registry, float dt)
{
    for (const Entity ID : registry.getEntities<CEnemyHoming>())
    {
        CRigidbody& rigidbody = registry.getComponent<CRigidbody>(ID);
        const CEnemyHoming& homingComp = registry.getComponent<CEnemyHoming>(ID);
        const CTransform& transform = registry.getComponent<CTransform>(ID);
        const CTransform& playerTransform = registry.getComponent<CTransform>(registry.getEntities<CPlayer>()[0]);
        const vec2 diff = {playerTransform.pos.x-transform.pos.x,playerTransform.pos.y-transform.pos.y};
        rigidbody.acceleration+= utils::normalize(diff)*homingComp.moveSpeed;
        
    }
}

void SEnemy::spawnWave(Registry& registry, float difficultyMultiplier)
{
    const float multiplier = FRAND_RANGE(1.0f, 1.5f)*difficultyMultiplier;
    factory::createEnemyTank(registry, {800.0f*difficultyMultiplier,300.0f}, {20.0f,8.0f},10.0f,50.0f*multiplier, 10.0f*multiplier, 200.0f,15000.0f*multiplier, 25.0f *multiplier, 20.0f*multiplier, 10.0f*multiplier,30.0f,5.0f*multiplier);
    factory::createEnemyTank(registry, {900.0f*difficultyMultiplier,500.0f}, {30.0f,10.0f},15.0f,75.0f*multiplier, 10.0f*multiplier, 150.0f,20000.0f*multiplier, 30.0f *multiplier, 30.0f*multiplier, 10.0f*multiplier,40.0f, 6.0f*multiplier);
    factory::createEnemyHoming(registry, {1000.0f*difficultyMultiplier,400.0f},20.0f*multiplier, 6,20.0f*multiplier, 10.0f*multiplier,600.0f*multiplier);
}

