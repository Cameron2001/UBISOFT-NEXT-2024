#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"

class SEnemy : public ISystem
{
public:
    void Update(Registry& Registry, float dt);
private:
    void UpdateTanks(Registry& Registry, float dt);
    void UpdateHoming(Registry& Registry, float dt);
    void SpawnWave(Registry& Registry, float difficultyMultiplier);
};
