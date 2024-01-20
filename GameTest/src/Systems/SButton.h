#pragma once
#include "ISystem.h"
#include "../Core/Scene.h"
#include "../Util/Vectors.h"

class SButton : public ISystem
{
public:
    void Update(Scene& scene, float dt);
    void CheckClicks(Scene& scene);
    void ResolveClicks(Scene& scene);
    void StartClick(Scene& scene);
    void TutorialClick(Scene& scene);
    void ExitClick(Scene& scene);
    void RetryClick(Scene& scene);
    bool Clicked(vec2 mousePos,vec2 buttonPos,vec2 bounds);
    
};
