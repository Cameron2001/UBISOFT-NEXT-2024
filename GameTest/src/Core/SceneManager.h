#pragma once
#include "Scene.h"

class SceneManager
{
protected:
    SceneManager();

public:
    ~SceneManager();
    
    
    void Update(float dt) const;
    void Render() const;
    void CleanUp();
    
    static SceneManager* GetInstance();
    template<typename T>
    void LoadScene()
    {
        CleanUp();
		
        currentScene = new T();
        currentScene->Init();
    }

private:
    static SceneManager* instance;
    Scene* currentScene;
};