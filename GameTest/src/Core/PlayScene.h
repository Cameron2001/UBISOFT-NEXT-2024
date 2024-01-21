//------------------------------------------------------------------------
// PlayScene.h
//------------------------------------------------------------------------
#pragma once
#include "Scene.h"

class PlayScene final : public Scene
{
public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void shutdown() override;
private:
    void createSystems();
    void createComponentArrays();
    void createMap();
};
