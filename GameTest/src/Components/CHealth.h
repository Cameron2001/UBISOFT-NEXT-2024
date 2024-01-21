#pragma once
struct CHealth
{
    float hp;
    float maxHp;
    float regenRate;
    bool bDead = false;
    CHealth(const float health = 100, float regenRate = 1.0f): hp(health),maxHp(health),regenRate(regenRate){}
};
