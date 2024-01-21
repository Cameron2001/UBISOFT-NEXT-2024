#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
#include "../Util/Vectors.h"

class SArm : public ISystem
{
public:
    void Update(Registry& Registry);
    
};
