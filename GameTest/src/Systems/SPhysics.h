#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Registry.h"
class SPhysics : public ISystem
{
public:
    void Update(Registry& Registry, float dt);

private:
    //create an array of current collisions
    bool BoxBox(Registry& Registry, Entity aID, Entity bID);
    bool BoxCircle(Registry& Registry, Entity boxID, Entity circleID);
    bool CircleCircle(Registry& Registry, Entity aID, Entity bID);
    void ResolveCollisions(Registry& Registry);
    void CheckCollisions(Registry& Registry);
    bool CheckCollision(Registry& Registry, Entity a, Entity b);
    void ApplyKinematics(Registry& Registry, float dt);
    void DeleteOffscreen(Registry& Registry);
    
};

