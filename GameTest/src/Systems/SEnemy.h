//------------------------------------------------------------------------
// SEnemy.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ISystem.h"
#include "../Core/Registry.h"

//------------------------------------------------------------------------
class SEnemy : public ISystem
{
public:
    static void start(Registry& registry);
    static void update(Registry& registry);

private:
    static void updateTanks(Registry& registry);
    static void updateHoming(Registry& registry);
    static void spawnWave(Registry& registry, float difficultyMultiplier);
};
