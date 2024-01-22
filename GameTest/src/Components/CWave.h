//------------------------------------------------------------------------
// CWave.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CWave
{
    float waveCooldown;
    //used to scale enemy stats based on time elapsed
    float difficultyMultiplier;
    CWave(
        float waveCooldown = 10.0f,
        float difficultyMultiplier = 1.0f
        ):
        waveCooldown(waveCooldown),
        difficultyMultiplier(difficultyMultiplier)
    {}
};