#include "stdafx.h"
#include "Scene.h"
#include "ComponentArray.h"
#include "../Components/CTransform.h"

Scene::Scene()
{
    //create Component arrays
}

void Scene::Init()
{
    SetCamera(Camera());
    auto player = CreateEntity();
    
    auto transformArray = ComponentArray<CTransform>(32,32);
    transformArray.AddComponent(player, CTransform(vec2(5,5),90));
    bool test = transformArray.HasEntity(player);
    transformArray.RemoveComponent(player);
    test = transformArray.HasEntity(player);
    
    
    
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
    m_entityArray.push_back(1);
    return 1;
}

void Scene::DeleteEntity(Entity entityID)
{
}

template <typename T>
bool Scene::HasComponent(Entity entityID)
{
    return true;
}

template <typename T>
T Scene::GetComponent(Entity entityID)
{
    return 0;
}

template <typename T>
void Scene::AddComponent(Entity entityID, T component)
{
}

template <typename T>
void Scene::DeleteComponent(Entity entityID, T component)
{
}

void Scene::SetCamera(Camera cam)
{
    m_camera = cam;
}

Camera Scene::GetCamera()
{
    return m_camera;
}

