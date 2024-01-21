#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
#include "../Util/Vectors.h"

class SButton : public ISystem
{
public:
    void Update(Registry& Registry);
private:
    void CheckClicks(Registry& Registry);
    void ResolveClicks(Registry& Registry);
    void StartClick();
    void ExitClick();
    bool Clicked(vec2 mousePos,vec2 buttonPos,vec2 bounds);
    
};
