#pragma once
struct CShield
{
    bool isEnabled = false;
    float health;
    CShield(float health = 100.0f): health(health){}
};
