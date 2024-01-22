//------------------------------------------------------------------------
// DeathScene.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "Scene.h"
//------------------------------------------------------------------------

class DeathScene : public Scene
{
public:
    DeathScene(float timer = 0.0f):timeSurvived(timer){}
    void init() override;
    void update(float dt) override;
    void render() override;
    void shutdown() override;
private:
    void createSystems();
    void createComponentArrays();
    void createMenu();
    float timeSurvived;
};
