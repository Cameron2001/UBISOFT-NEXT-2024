#pragma once
#include "Scene.h"

class ECSTestScene : public Scene
{
public:
    void Init() override;
    void Update(float dt) override;
    void Shutdown() override;
    
};
