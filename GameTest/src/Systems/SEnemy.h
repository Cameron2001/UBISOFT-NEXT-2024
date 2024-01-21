#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"

class SEnemy : public ISystem
{
public:
    void Update(Scene& scene, float dt);
private:
    void UpdateTanks(Scene& scene, float dt);
    void UpdateHoming(Scene& scene, float dt);
    void SpawnWave(Scene& scene, float difficultyMultiplier);
};
