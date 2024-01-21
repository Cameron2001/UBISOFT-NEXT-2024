#pragma once
struct CHealth
{
    float hp;
    float maxHp;
    float regenRate;
    CHealth(const float health = 100, float regenRate = 5.0f): hp(health),maxHp(health),regenRate(regenRate){}
};
