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
	SceneManager::GetInstance()->LoadScene<MenuScene>();
}
void Update(float deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);
}
void Render()
{
	SceneManager::GetInstance()->Render();
}
void Shutdown()
{
	SceneManager::GetInstance()->Shutdown();
}