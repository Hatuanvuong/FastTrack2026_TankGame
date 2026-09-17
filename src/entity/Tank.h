#pragma once

#include "../core/Constants.h"
#include "../core/Direction.h"
#include "../core/PlayerId.h"

// Represents a tank controlled by a player.
struct Tank
{
    // X position of the Tank's top-left corner in pixels.
    float x;

    // Y position of the Tank's top-left corner in pixels.
    float y;

    // Current HP of the tank.
    int hp;

    // Current facing direction.
    Direction direction;

    // Owner of this tank.
    PlayerId playerId;

    // Movement speed in pixels per second.
    float speed;

    // Creates a tank with default values defined by the game specification.
    Tank()
    {
        x = 0.0f;
        y = 0.0f;

        hp = Constants::TANK_HP;

        direction = Up;

        playerId = Player1;

        speed = Constants::TANK_SPEED;
    }
};