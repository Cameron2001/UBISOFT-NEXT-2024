﻿//------------------------------------------------------------------------
// SPlayer.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ISystem.h"
#include "../Core/Registry.h"

//------------------------------------------------------------------------
class SPlayer : public ISystem
{
public:
    static void update(Registry& registry);
};
