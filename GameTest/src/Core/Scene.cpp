#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
    //create Component arrays
    
}

void Scene::Init()
{
    Entity player = CreateEntity();
}

void Scene::Update(float dt)
{
}

void Scene::Render()
{
}

void Scene::Shutdown()
{
}

Entity Scene::CreateEntity()
{
    return 1;
}

void Scene::DeleteEntity(Entity entityID)
{
}

template <typename T>
bool Scene::HasComponent(Entity entityID)
{
}

template <typename T>
T Scene::GetComponent(Entity entityID)
{
}

template <typename T>
void Scene::AddComponent(Entity entityID, T component)
{
}

template <typename T>
void Scene::DeleteComponent(Entity entityID, T component)
{
}

Camera Scene::GetCamera()
{
    return m_camera;
}
