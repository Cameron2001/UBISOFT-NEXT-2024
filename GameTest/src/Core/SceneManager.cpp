//------------------------------------------------------------------------
// SceneManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;



SceneManager::SceneManager()
{
    currentScene = nullptr;
}

SceneManager::~SceneManager()
{
    cleanUp();
}

void SceneManager::update(float dt) const
{
    currentScene->update(dt);
}

void SceneManager::render() const
{
    currentScene->render();
}

void SceneManager::cleanUp()
{
    if (currentScene)
    {
        currentScene->shutdown();
        delete currentScene;
        currentScene = nullptr;
    }
}









SceneManager* SceneManager::getInstance()
{
    if (instance == nullptr)
        instance= new SceneManager();

    return instance;
}