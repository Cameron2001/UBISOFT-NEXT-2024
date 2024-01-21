#pragma once

struct CPlayer
{
    float moveSpeed;
    float damageScale = 1.0f;
    float shootCooldown= 1.0f;
    CPlayer(float speed=300):moveSpeed(speed){}
};
