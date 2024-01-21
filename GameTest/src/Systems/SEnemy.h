#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"

class SEnemy : public ISystem
{
public:
    void update(Registry& registry, float dt);
private:
    void updateTanks(Registry& registry, float dt);
    void updateHoming(Registry& registry, float dt);
    void spawnWave(Registry& registry, float difficultyMultiplier);
};
