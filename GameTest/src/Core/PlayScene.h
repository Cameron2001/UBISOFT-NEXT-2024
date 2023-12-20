#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
public:
    ~PlayScene() override;
    void Init() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;
private:
    Entity m_player;
};
