#pragma once

#include "../game/World.h"
#include "BulletSystem.h"
#include <SDL3/SDL.h>

// Responsible for handling keyboard input.
class InputSystem
{
public:
    // Updates tank movement and rotation.
    void Update(World& world, float deltaTime);

    // Handles bullet firing input.
    void HandleFireInput(World& world,
                         const SDL_Event& event,
                         BulletSystem& bulletSystem);

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