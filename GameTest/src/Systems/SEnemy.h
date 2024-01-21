#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"

class SEnemy : public ISystem
{
public:
    void update(Registry& Registry, float dt);
private:
    void updateTanks(Registry& Registry, float dt);
    void updateHoming(Registry& Registry, float dt);
    void spawnWave(Registry& Registry, float difficultyMultiplier);
};
