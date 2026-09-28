#pragma once

#include "../map/Map.h"
#include "../entity/Tank.h"
#include "../entity/Bullet.h"
#include <vector>

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

    // Bullet fired by Player 1.
    std::vector<Bullet> player1Bullets;

    // Bullet fired by Player 2.
    std::vector<Bullet> player2Bullets;

    // This can be expanded later: Timer, GameState

private:
    // Initializes all world objects.
    void Initialize();
};