#include "stdafx.h"
#include "SEnemy.h"

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
    for (const auto element : Registry.GetEntities<CEnemyTank>())
    {
        CEnemyTank* tank = Registry.GetComponent<CEnemyTank>(element);
        CRigidbody* rb = Registry.GetComponent<CRigidbody>(element);
        CTimer* timer = Registry.GetComponent<CTimer>(element);
        CArm* arm = Registry.GetComponent<CArm>(element);
        const CTransform* transform = Registry.GetComponent<CTransform>(element);
        const CCircleCollider* circle = Registry.GetComponent<CCircleCollider>(element);
        const CTransform* playerTransform = Registry.GetComponent<CTransform>(Registry.GetEntities<CPlayer>()[0]);
        const vec2 armStart = transform->pos+circle->offset;
        
        arm->rotation =atan2f(playerTransform->pos.y-armStart.y,playerTransform->pos.x-armStart.x);
        if(arm->rotation*Utils::Rad2Deg < 0) arm->rotation+=Utils::Deg2Rad*360;
        arm->rotation = Utils::Clamp(arm->rotation,75*Utils::Deg2Rad, 255*Utils::Deg2Rad);
        
        if(tank->state == CEnemyTank::TankState::IDLE)
        {
            tank->state = CEnemyTank::TankState::SHOOTING;
            timer->timer = 0;
        }
        if(tank->state == CEnemyTank::TankState::SHOOTING)
        {
            if(timer->timer > 1.0f)
            {
                
                Factory::CreateProjectile(Registry,armStart,16*timer->timer, tank->projectileForce*timer->timer,arm->rotation,tank->projectileHealth*timer->timer,tank->projectileDmg*timer->timer);
                timer->timer = 0.0f;
                tank->state = CEnemyTank::TankState::RELOADING;
            }
        }
        if(tank->state == CEnemyTank::TankState::RELOADING)
        {
            
            if(timer->timer>3.0f)
            {
                timer->timer = 0.0f;
                tank->state = CEnemyTank::TankState::IDLE;
            }
        }
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
    Factory::CreateEnemyTank(Registry, {800*difficultyMultiplier,300}, {20,8},10,100*difficultyMultiplier, 15.0f*difficultyMultiplier, 200,25000*difficultyMultiplier, 25 *difficultyMultiplier, 20*difficultyMultiplier);
    Factory::CreateEnemyTank(Registry, {900*difficultyMultiplier,500}, {30,10},15,150*difficultyMultiplier, 25.0f*difficultyMultiplier, 150,30000*difficultyMultiplier, 50 *difficultyMultiplier, 35*difficultyMultiplier);
    Factory::CreateEnemyHoming(Registry, {1000*difficultyMultiplier,400},20*difficultyMultiplier,100*difficultyMultiplier, 20*difficultyMultiplier,600*difficultyMultiplier);
}

