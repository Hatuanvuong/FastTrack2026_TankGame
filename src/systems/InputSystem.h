#pragma once

#include "../game/World.h"

// Responsible for handling keyboard input.
class InputSystem
{
public:
    // Updates tank movement and rotation.
    void Update(World& world, float deltaTime);

private:
    // Checks whether the tank can move to the next position.
    bool CanMoveTo(const World& world,
                   const Tank& otherTank,
                   float nextX,
                   float nextY) const;

    // Checks whether the next position would collide with BorderWall, ObstacleWall
    bool IsMapCollision(const World& world,
                        float nextX,
                        float nextY) const;

    // Checks whether the next position would collide with another tank.
    bool IsTankCollision(const Tank& otherTank,
                         float nextX,
                         float nextY) const;
};