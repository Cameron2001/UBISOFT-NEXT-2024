#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Scene.h"
class SPhysics : public ISystem
{
public:
    void Update(Scene* scene, float dt);

private:
    //create an array of current collisions
    bool BoxBox(Scene* scene, Entity aID, Entity bID);
    bool BoxCircle(Scene* scene, Entity boxID, Entity circleID);
    
    bool CircleCircle(Scene* scene, Entity aID, Entity bID);

    void ResolveImpulses(Scene* scene);
    void ResolveCollisions(Scene* scene);

    void CheckCollisions(Scene* scene);
    bool CheckCollision(Scene* scene, Entity a, Entity b);
    void ApplyKinematics(Scene* scene, float dt);
    
};

