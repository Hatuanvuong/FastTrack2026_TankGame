#pragma once

#include "../core/Direction.h"
#include "../core/PlayerId.h"

// Represents a bullet fired by a tank.
struct Bullet
{
    // X position of the bullet's top-left corner in pixels.
    float x;

    // Y position of the bullet's top-left corner in pixels.
    float y;

    // Current moving direction of the bullet.
    Direction direction;

    // Owner of the bullet.
    PlayerId owner;

    // Indicates whether the bullet is currently active.
    // true  : bullet exists in the game world
    // false : bullet is inactive or destroyed
    bool active;

    // Creates a bullet with default values.
    Bullet()
    {
        x = 0.0f;
        y = 0.0f;

        direction = Up;

        owner = Player1;

        active = false;
    }
};