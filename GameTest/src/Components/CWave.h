#pragma once
struct CWave
{
    float waveCooldown = 10.0f;
    float difficultyMultiplier = 1.0f;
    CWave(float coolDown = 10.0f):waveCooldown(coolDown){}
};