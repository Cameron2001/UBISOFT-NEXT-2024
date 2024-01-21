#pragma once
struct CEnemyTank
{
    enum class TankState
    {
        SHOOTING,
        RELOADING,
        IDLE
    };
    TankState state = TankState::IDLE;
    float projectileForce;
    float projectileDmg;
    float projectileHealth;
    float moveSpeed;
    float rot;
    float armLength;
    CEnemyTank(float projDmg, float projForce, float projHp = 100.0f, float moveSpeed = 50.0f): projectileForce(projForce), rot(0.0f), armLength(50.0f), projectileDmg(projDmg),moveSpeed(moveSpeed), projectileHealth(projHp)
    {
    }
};
