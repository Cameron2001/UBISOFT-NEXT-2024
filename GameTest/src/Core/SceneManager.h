//------------------------------------------------------------------------
// SceneManager.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "Scene.h"
//------------------------------------------------------------------------
//singleton
class SceneManager
{
protected:
    SceneManager();

public:
    ~SceneManager();
    
    
    void update(float dt) const;
    void render() const;
    void cleanUp();
    
    static SceneManager* getInstance();
    template<typename T>
    void loadScene()
    {
        cleanUp();
        currentScene = new T();
        currentScene->init();
    }
    template<typename T>
    void loadScene(float timer)
    {
        cleanUp();
        currentScene = new T(timer);
        currentScene->init();
    }

private:
    static SceneManager* instance;
    Scene* currentScene;
};