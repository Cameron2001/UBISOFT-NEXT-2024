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
    void StartClick(Registry& Registry);
    void TutorialClick(Registry& Registry);
    void ExitClick(Registry& Registry);
    void RetryClick(Registry& Registry);
    bool Clicked(vec2 mousePos,vec2 buttonPos,vec2 bounds);
    
};
