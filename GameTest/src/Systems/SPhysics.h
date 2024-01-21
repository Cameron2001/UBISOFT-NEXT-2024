#pragma once
#include "ISystem.h"
#include "../Components/Components.h"
#include "../Core/Registry.h"
class SPhysics : public ISystem
{
public:
    void update(Registry& Registry, float dt);

private:
    //create an array of current collisions
    bool boxBox(Registry& Registry, Entity aID, Entity bID);
    bool boxCircle(Registry& Registry, Entity boxID, Entity circleID);
    bool circleCircle(Registry& Registry, Entity aID, Entity bID);
    void resolveCollisions(Registry& Registry);
    void checkCollisions(Registry& Registry);
    bool checkCollision(Registry& Registry, Entity a, Entity b);
    void applyKinematics(Registry& Registry, float dt);
    void deleteOffscreen(Registry& Registry);
    
};

