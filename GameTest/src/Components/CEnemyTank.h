﻿//------------------------------------------------------------------------
// CEnemyTank.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct CEnemyTank
{
    float moveSpeed;

    CEnemyTank(
        const float moveSpeed = 50.0f
    ):
        moveSpeed(moveSpeed)
    {
    }
};
