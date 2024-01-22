//------------------------------------------------------------------------
// CHealth.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CHealth
{
    float health;
    float maxHealth;
    float regenRate;
    bool bDead = false;
    CHealth(
        float health = 100.0f,
        float regenRate = 1.0f
        ):
        health(health),
        maxHealth(health),
        regenRate(regenRate)
    {}
};
