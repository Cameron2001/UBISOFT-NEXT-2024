//------------------------------------------------------------------------
// SceneManager.h
//------------------------------------------------------------------------
#pragma once
#include "Scene.h"

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

private:
    static SceneManager* instance;
    Scene* currentScene;
};