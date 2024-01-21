//------------------------------------------------------------------------
// CHealth.h
//------------------------------------------------------------------------
#pragma once
struct CHealth
{
    float health;
    float maxHealth;
    float regenRate;
    bool bDead = false;
    CHealth(const float health = 100, float regenRate = 1.0f): health(health),maxHealth(health),regenRate(regenRate){}
};
