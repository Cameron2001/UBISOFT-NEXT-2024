#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
struct Collision
{
    Entity entityA;
    Entity entityB;
    vec2 mtv;
    Collision(Entity a, Entity b, vec2 minimumTranslation = {0,0}): entityA(a), entityB(b), mtv(minimumTranslation){};
};
class SPhysics : public ISystem
{
public:
    void Update(Scene* scene, float dt);

private:
    //create an array of current collisions
    bool BoxBox(Scene* scene, Entity aID, Entity bID);
    bool BoxCircle(Scene* scene, Entity boxID, Entity circleID);
    bool BoxPlane(Scene* scene, Entity boxID, Entity planeID);
    
    bool CircleCircle(Scene* scene, Entity aID, Entity bID);
    bool CirclePlane(Scene* scene, Entity circleID, Entity planeID);

    void ResolveCollisions(Scene* scene);

    void CheckCollisions(Scene* scene);
    bool CheckCollision(Scene* scene, Entity a, Entity b);
    void ApplyKinematics(Scene* scene, float dt);

    std::vector<Collision> collisions;
};

