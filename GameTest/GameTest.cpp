//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "src/Core/ECSTestScene.h"
#include "src/Core/MenuScene.h"
#include "src/Core/PlayScene.h"
//PlayScene* scene;
MenuScene* scene;
//ECSTestScene* scene;
void Init()
{
	//scene = new PlayScene;
	scene = new MenuScene;
	scene->Init();
}
void Update(float deltaTime)
{
	scene->Update(deltaTime);
}
void Render()
{
	scene->Render();
}
void Shutdown()
{
	scene->Shutdown();
	delete scene;
}