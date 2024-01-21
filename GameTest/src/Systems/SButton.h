//------------------------------------------------------------------------
// SButton.h
//------------------------------------------------------------------------
#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
#include "../Util/Vectors.h"

class SButton : public ISystem
{
public:
    void update(Registry& registry);
private:
    static void checkClicks(Registry& registry);
    static void resolveClicks(Registry& registry);
    static bool clicked(vec2 mousePos,vec2 buttonPos,vec2 bounds);
    
};
