#pragma once
#include "ISystem.h"
#include "../Core/Registry.h"
class SPhysics : public ISystem
{
public:
    void update(Registry& registry, float dt);

private:
    //create an array of current collisions
    bool boxBox(Registry& registry, Entity aID, Entity bID);
    bool boxCircle(Registry& registry, Entity boxID, Entity circleID);
    bool circleCircle(Registry& registry, Entity aID, Entity bID);
    void resolveCollisions(Registry& registry);
    void checkCollisions(Registry& registry);
    bool checkCollision(Registry& registry, Entity a, Entity b);
    void applyKinematics(Registry& registry, float dt);
    void deleteOffscreen(Registry& registry);
    
};

