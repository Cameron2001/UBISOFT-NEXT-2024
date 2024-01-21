#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"

class SEnemy : public ISystem
{
public:
    void update(Registry& registry, float dt);
private:
    static void updateTanks(Registry& registry, float dt);
    static void updateHoming(Registry& registry, float dt);
    static void spawnWave(Registry& registry, float difficultyMultiplier);
};
