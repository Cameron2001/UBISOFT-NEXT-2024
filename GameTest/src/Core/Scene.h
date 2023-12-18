#pragma once
#include "Camera.h"
#include "ComponentArray.h"
#include "../Systems/ISystem.h"

enum Components
{
    
};
enum Systems
{
    
};
class Scene
{
public:
    Scene();
    void Init();
    void Update(float dt);
    void Render();
    void Shutdown();
    
    Entity CreateEntity();
    void DeleteEntity(Entity entityID);

    template<typename T>
    bool HasComponent(Entity entityID);

    template<typename T>
    T GetComponent(Entity entityID);

    template<typename T>
    void AddComponent(Entity entityID, T component);

    template<typename T>
    void DeleteComponent(Entity entityID, T component);

    template<typename T>
    void CreateComponentArray();
    
    template<typename T>
    T GetComponentArray();

    template<typename T>
    void CreateSystem();
    
    template<typename T>
    T GetSystem();
    
    Camera m_camera;
    Entity m_player;
private:
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids
    std::vector<IComponentArray*> m_componentArrays;
    std::vector<ISystem*> m_sysyemArray;
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    
    

    
    //create 2d array that holds component array
};
