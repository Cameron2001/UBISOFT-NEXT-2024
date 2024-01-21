//------------------------------------------------------------------------
// CWave.h
//------------------------------------------------------------------------
#pragma once
struct CWave
{
    float waveCooldown;
    float difficultyMultiplier;
    CWave(float waveCooldown = 10.0f, float difficultyMultiplier = 1.0f):waveCooldown(waveCooldown),difficultyMultiplier(difficultyMultiplier){}
};