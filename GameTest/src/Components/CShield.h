//------------------------------------------------------------------------
// CShield.h
//------------------------------------------------------------------------
#pragma once
struct CShield
{
    bool bEnabled;
    float health;
    CShield(float health = 100.0f, bool bEnabled = false): health(health),bEnabled(bEnabled){}
};
