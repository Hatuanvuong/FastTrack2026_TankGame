#pragma once

#include "../game/World.h"

// Responsible for handling keyboard input.
class InputSystem
{
public:
    // Updates tank movement and rotation.
    void Update(World& world, float deltaTime);
};