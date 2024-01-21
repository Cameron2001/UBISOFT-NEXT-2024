//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "src/Core/MenuScene.h"
#include "src/Core/PlayScene.h"
#include "src/Core/SceneManager.h"

//MenuScene* scene;
//ECSTestScene* scene;
void Init()
{
	SceneManager::getInstance()->loadScene<MenuScene>();
}
void Update(float deltaTime)
{
	SceneManager::getInstance()->update(deltaTime);
}
void Render()
{
	SceneManager::getInstance()->render();
}
void Shutdown()
{
	SceneManager::getInstance()->cleanUp();
}