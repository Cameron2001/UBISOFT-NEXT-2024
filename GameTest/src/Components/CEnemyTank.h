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
    float projectileSpeed;
    float rot;
    float armLength;
    CEnemyTank(float speed = 50, float rotation = 0, float length=100):projectileSpeed(speed),rot(rotation),armLength(length){}
};
