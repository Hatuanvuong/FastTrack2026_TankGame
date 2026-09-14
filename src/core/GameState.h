#pragma once

#include "Map.h"
#include "Tank.h"

struct GameState
{
    Map map;

    Tank player1;
    Tank player2;

    int remainingTime;
};