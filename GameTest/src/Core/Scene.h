#pragma once
#include <typeindex>
#include <unordered_map>

#include "Camera.h"
#include "ComponentArray.h"
#include "../Systems/ISystem.h"

enum class Components
{
    Audio,
    BoxCollider,
    Button,
    CapsuleCollider,
    CircleCollider,
    Color,
    Label,
    Player,
    Rigidbody,
    Sprite,
    Transform,
    NumOfComponents
};
enum class Systems
{
    Physics,
    Player,
    Render
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
    void RemoveComponent(Entity entityID, T component);

    template<typename T>
    void CreateComponentArray();

    template<typename T>
    ComponentArray<T>* GetComponentArray();

    template<typename T>
    bool HasComponentArray();

    template<typename T>
    void CreateSystem();

    template<typename T>
    void GetSystem();

    template<typename T>
    bool HasSystem();
    
    
    Camera m_camera;
    Entity m_player;
private:
    std::vector<Entity> m_entityArray; //just a vector of uint32_t. Hold all entity ids
    std::unordered_map<const char*, IComponentArray*> m_componentMap;
    std::unordered_map<const char*, ISystem*> m_systemMap;
    Entity entityNum=0;
    //maybe create some type of storage to contain all systems in
    //maybe vector isnt correct storage. If an entity is removed the index and entityID will no longer be alligned
    
    

    
};
