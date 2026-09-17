#pragma once

#include "../core/PlayerId.h"

// Represents a player in the match.
struct Player
{
    // Unique player identifier.
    PlayerId playerId;

    // Creates a player with default values.
    Player()
    {
        playerId = Player1;
    }
};