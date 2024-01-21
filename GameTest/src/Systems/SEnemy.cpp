#include "stdafx.h"
#include "SEnemy.h"

#include "../../app/AppSettings.h"
#include "../Components/Components.h"
#include "../Core/Factory.h"
#include "../Util/Utils.h"

void SEnemy::Update(Registry& Registry, float dt)
{
    const auto waveController = Registry.GetEntities<CWave>()[0];
    CTimer* timer = Registry.GetComponent<CTimer>(waveController);
    const CWave* wave = Registry.GetComponent<CWave>(waveController);
    if(timer->timer>wave->waveCooldown)
    {
        timer->timer = 0.0f;
        SpawnWave(Registry, wave->difficultyMultiplier);
    }
    UpdateTanks(Registry,dt);
    UpdateHoming(Registry,dt);
}

void SEnemy::UpdateTanks(Registry& Registry, float dt)
{
    auto playerPos = Registry.GetComponent<CTransform>(Registry.GetEntities<CPlayer>()[0])->pos;
    for (const auto element : Registry.GetEntities<CEnemyTank>())
    {
        CRigidbody* rb = Registry.GetComponent<CRigidbody>(element);
        CEnemyTank* tank = Registry.GetComponent<CEnemyTank>(element);
        CTransform* transform = Registry.GetComponent<CTransform>(element);
        CCircleCollider* circle = Registry.GetComponent<CCircleCollider>(element);
        CArm* arm = Registry.GetComponent<CArm>(element);

        const vec2 armStart = transform->pos+circle->offset;
        arm->rotation =atan2f(playerPos.y-armStart.y,playerPos.x-armStart.x);
        if(arm->rotation*Utils::Rad2Deg < 0) arm->rotation+=Utils::Deg2Rad*360;
        arm->rotation = Utils::Clamp(arm->rotation,75*Utils::Deg2Rad, 255*Utils::Deg2Rad);
        
        rb->acceleration.x-=tank->moveSpeed;
        
    }
}

void SEnemy::UpdateHoming(Registry& Registry, float dt)
{
    for (auto element : Registry.GetEntities<CEnemyHoming>())
    {
        CEnemyHoming* homingComp = Registry.GetComponent<CEnemyHoming>(element);
        CRigidbody* rigidbody = Registry.GetComponent<CRigidbody>(element);
        CTransform* transform = Registry.GetComponent<CTransform>(element);
        const CTransform* playerTransform = Registry.GetComponent<CTransform>(Registry.GetEntities<CPlayer>()[0]);
        vec2 diff = {playerTransform->pos.x-transform->pos.x,playerTransform->pos.y-transform->pos.y};
        rigidbody->acceleration+= Utils::Normalize(diff)*homingComp->moveSpeed;
        
    }
}

void SEnemy::SpawnWave(Registry& Registry, float difficultyMultiplier)
{
    float multiplier = FRAND_RANGE(1.0f, 1.5f)*difficultyMultiplier;
    Factory::CreateEnemyTank(Registry, {800*difficultyMultiplier,300}, {20,8},10,50*multiplier, 10.0f*multiplier, 200,15000*multiplier, 25 *multiplier, 20*multiplier, 10.0f*multiplier,30.0f,5.0f*multiplier);
    Factory::CreateEnemyTank(Registry, {900*difficultyMultiplier,500}, {30,10},15,75*multiplier, 10.0f*multiplier, 150,20000*multiplier, 30 *multiplier, 30*multiplier, 10.0f*multiplier,40.0f, 6.0*multiplier);
    Factory::CreateEnemyHoming(Registry, {1000*difficultyMultiplier,400},20*multiplier, 6,20*multiplier, 10*multiplier,600*multiplier);
}

