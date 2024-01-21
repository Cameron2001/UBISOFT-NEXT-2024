#pragma once
#include "Scene.h"

class PlayScene final : public Scene
{
public:
    void Init() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;
private:
    void CreateSystems();
    void CreateComponentArrays();
    void CreateMap();
};
