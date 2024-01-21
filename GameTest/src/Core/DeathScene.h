#pragma once
#include "Scene.h"

class DeathScene : public Scene
{
public:
    void Init() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;
private:
    void CreateSystems();
    void CreateComponentArrays();
    void CreateMenu();
};
