#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
#include "../Util/Vectors.h"

class SButton : public ISystem
{
public:
    void update(Registry& registry);
private:
    void checkClicks(Registry& registry);
    void resolveClicks(Registry& registry);
    void startClick();
    void exitClick();
    bool clicked(vec2 mousePos,vec2 buttonPos,vec2 bounds);
    
};
