#pragma once

#include "../map/Map.h"
#include "../entity/Tank.h"

// Represents the current game world. World contains all gameplay data that belongs to a match.
class World
{
public:
    World();

    // Game map.
    Map map;

    // Tank controlled by Player 1.
    Tank player1Tank;

    // Tank controlled by Player 2.
    Tank player2Tank;

    // This can be expanded later: Bullets, Timer, GameState

private:
    // Initializes all world objects.
    void Initialize();
};