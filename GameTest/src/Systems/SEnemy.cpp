#include "stdafx.h"
#include "SEnemy.h"

#include "../Components/CDamageEvent.h"
#include "../Components/CEnemyTank.h"
#include "../Components/CHealth.h"
#include "../Components/CRender.h"

void SEnemy::Update(Scene& scene, float dt)
{
    
}

void SEnemy::UpdateTanks(Scene& scene, float dt)
{
    for (auto element : scene.reg.GetEntities<CEnemyTank>())
    {
        CEnemyTank* tank = scene.reg.GetComponent<CEnemyTank>(element);
    }
}

void SEnemy::SpawnWave(Scene& scene, float dt)
{
    
}

