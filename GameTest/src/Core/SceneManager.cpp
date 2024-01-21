#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;



SceneManager::SceneManager()
{
    currentScene = nullptr;
}

SceneManager::~SceneManager()
{
    Shutdown();
}

void SceneManager::Update(float dt) const
{
    currentScene->Update(dt);
}

void SceneManager::Render() const
{
    currentScene->Render();
}
void SceneManager::Shutdown()
{
    if (currentScene)
    {
        currentScene->Shutdown();
        delete currentScene;
        currentScene = nullptr;
    }
}







SceneManager* SceneManager::GetInstance()
{
    if (instance == nullptr)
        instance= new SceneManager();

    return instance;
}