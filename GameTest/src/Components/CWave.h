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
        const float waveCooldown = 10.0f,
        const float difficultyMultiplier = 1.0f
    ):
        waveCooldown(waveCooldown),
        difficultyMultiplier(difficultyMultiplier)
    {
    }
};
