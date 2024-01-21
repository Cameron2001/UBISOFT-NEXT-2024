#pragma once
struct CShield
{
    bool bEnabled = false;
    float health;
    CShield(float health = 100.0f): health(health){}
};
