#pragma once
struct CHealth
{
    float hp;
    float maxHp;
    CHealth(const float health = 100): hp(health),maxHp(health){}
};
