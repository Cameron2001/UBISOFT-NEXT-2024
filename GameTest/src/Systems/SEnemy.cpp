#include "stdafx.h"
#include "SEnemy.h"

#include "SFactory.h"
#include "../Components/Components.h"
#include "../Util/Utils.h"

void SEnemy::Update(Scene& scene, float dt)
{
    const auto waveController = scene.reg.GetEntities<CWave>()[0];
    CTimer* timer = scene.reg.GetComponent<CTimer>(waveController);
    const CWave* wave = scene.reg.GetComponent<CWave>(waveController);
    if(timer->timer>wave->waveCooldown)
    {
        timer->timer = 0.0f;
        SpawnWave(scene, wave->difficultyMultiplier);
    }
    UpdateTanks(scene,dt);
    UpdateHoming(scene,dt);
}

void SEnemy::UpdateTanks(Scene& scene, float dt)
{
    for (const auto element : scene.reg.GetEntities<CEnemyTank>())
    {
        CEnemyTank* tank = scene.reg.GetComponent<CEnemyTank>(element);
        CRigidbody* rb = scene.reg.GetComponent<CRigidbody>(element);
        CTimer* timer = scene.reg.GetComponent<CTimer>(element);
        CArm* arm = scene.reg.GetComponent<CArm>(element);
        const CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        const CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(element);
        const CTransform* playerTransform = scene.reg.GetComponent<CTransform>(scene.reg.GetEntities<CPlayer>()[0]);
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
                
                scene.reg.GetSystem<SFactory>()->CreateProjectile(scene,armStart,16*timer->timer, tank->projectileForce*timer->timer,arm->rotation,tank->projectileHealth*timer->timer,tank->projectileDmg*timer->timer);
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

void SEnemy::UpdateHoming(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CEnemyHoming>())
    {
        CEnemyHoming* homingComp = scene.reg.GetComponent<CEnemyHoming>(element);
        CRigidbody* rigidbody = scene.reg.GetComponent<CRigidbody>(element);
        CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        const CTransform* playerTransform = scene.reg.GetComponent<CTransform>(scene.reg.GetEntities<CPlayer>()[0]);
        vec2 diff = {playerTransform->pos.x-transform->pos.x,playerTransform->pos.y-transform->pos.y};
        rigidbody->acceleration+= Utils::Normalize(diff)*homingComp->moveSpeed;
        
    }
}

void SEnemy::SpawnWave(Scene& scene, float difficultyMultiplier)
{
    const auto factory = scene.reg.GetSystem<SFactory>();
    factory->CreateEnemyTank(scene, {800*difficultyMultiplier,300}, {20,8},10,100*difficultyMultiplier, 15.0f*difficultyMultiplier, 200,25000*difficultyMultiplier, 25 *difficultyMultiplier, 20*difficultyMultiplier);
    factory->CreateEnemyTank(scene, {900*difficultyMultiplier,500}, {30,10},15,150*difficultyMultiplier, 25.0f*difficultyMultiplier, 150,30000*difficultyMultiplier, 50 *difficultyMultiplier, 35*difficultyMultiplier);
    factory->CreateEnemyHoming(scene, {1000*difficultyMultiplier,400},20*difficultyMultiplier,100*difficultyMultiplier, 20*difficultyMultiplier,600*difficultyMultiplier);
}

