﻿#include "stdafx.h"
#include "SEnemy.h"

#include "SFactory.h"
#include "../Components/CBoxCollider.h"
#include "../Components/CCircleCollider.h"
#include "../Components/CDamageEvent.h"
#include "../Components/CEnemyTank.h"
#include "../Components/CHealth.h"
#include "../Components/CPlayer.h"
#include "../Components/CRender.h"
#include "../Components/CTransform.h"
#include "../Util/Utils.h"

void SEnemy::Update(Scene& scene, float dt)
{
    
    UpdateTanks(scene,dt);
}

void SEnemy::UpdateTanks(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CEnemyTank,CTransform,CBoxCollider,CCircleCollider,CRigidbody,CTimer>())
    {
        CEnemyTank* tank = scene.reg.GetComponent<CEnemyTank>(element);
        CTransform* transform = scene.reg.GetComponent<CTransform>(element);
        CBoxCollider* box = scene.reg.GetComponent<CBoxCollider>(element);
        CCircleCollider* circle = scene.reg.GetComponent<CCircleCollider>(element);
        CRigidbody* rb = scene.reg.GetComponent<CRigidbody>(element);
        CTransform* playerTransform = scene.reg.GetComponent<CTransform>(scene.reg.GetEntities<CPlayer>()[0]);
        CTimer* timer = scene.reg.GetComponent<CTimer>(element);
        vec2 armStart = transform->pos+circle->offset;
        
        tank->rot =atan2f(playerTransform->pos.y-armStart.y,playerTransform->pos.x-armStart.x);
        if(tank->rot*Utils::Rad2Deg < 0) tank->rot+=Utils::Deg2Rad*360;
        tank->rot = Utils::Clamp(tank->rot,75*Utils::Deg2Rad, 255*Utils::Deg2Rad);
        
        if(tank->state == CEnemyTank::TankState::IDLE)
        {
            tank->state = CEnemyTank::TankState::SHOOTING;
            timer->timer = 0;
        }
        if(tank->state == CEnemyTank::TankState::SHOOTING)
        {
            if(timer->timer > 1.0f)
            {
                
                scene.reg.GetSystem<SFactory>()->CreateProjectile(scene,armStart,20*timer->timer, 20000 *timer->timer,tank->rot,100*timer->timer,50*timer->timer);
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
        rb->acceleration.x-=50;
        
    }
}

void SEnemy::SpawnWave(Scene& scene, float dt)
{
    
}

