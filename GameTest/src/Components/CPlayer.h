//------------------------------------------------------------------------
// CPlayer.h
//------------------------------------------------------------------------
#pragma once

struct CPlayer
{
    float moveSpeed;
    float damageScale = 1.0f;
    CPlayer(float moveSpeed=300,float damageScale = 1.0f):moveSpeed(moveSpeed),damageScale(damageScale){}
};
