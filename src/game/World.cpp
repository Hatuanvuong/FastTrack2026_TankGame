#include "World.h"

#include "../core/Constants.h"

World::World()
{
    Initialize();
}

void World::Initialize()
{
    // Initialize Player 1 tank.
    player1Tank.x = Constants::PLAYER1_SPAWN_X;
    player1Tank.y = Constants::PLAYER1_SPAWN_Y;

    player1Tank.hp = Constants::TANK_HP;

    player1Tank.direction = Up;

    player1Tank.playerId = Player1;

    player1Tank.speed = Constants::TANK_SPEED;

    // Initialize Player 2 tank.
    player2Tank.x = Constants::PLAYER2_SPAWN_X;
    player2Tank.y = Constants::PLAYER2_SPAWN_Y;

    player2Tank.hp = Constants::TANK_HP;

    player2Tank.direction = Up;

    player2Tank.playerId = Player2;

    player2Tank.speed = Constants::TANK_SPEED;

    // This can be expanded later: Initialize Bullets, Timer, GameState
}
