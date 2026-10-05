#include "MatchSystem.h"

void MatchSystem::Update(World& world, float deltaTime)
{
    // Match has already ended.
    if (world.gameState != Playing)
    {
        return;
    }

    // Update the remaining match time.
    UpdateTimer(world, deltaTime);

    // Check whether either tank has been destroyed.
    CheckHpVictory(world);

    if (world.gameState != Playing)
    {
        return;
    }

    // Check timeout victory conditions.
    CheckTimeoutVictory(world);
}

void MatchSystem::Restart(World& world)
{
    // Restores the world to its initial state.
    world = World();
}

void MatchSystem::UpdateTimer(World& world, float deltaTime)
{
    world.remainingTime -= deltaTime;

    // Prevent negative time values.
    if (world.remainingTime < 0.0f)
    {
        world.remainingTime = 0.0f;
    }
}

void MatchSystem::CheckHpVictory(World& world)
{
    // Player 2 wins when Player 1 HP reaches zero.
    if (world.player1Tank.hp <= 0)
    {
        world.gameState = Player2Victory;
        return;
    }

    // Player 1 wins when Player 2 HP reaches zero.
    if (world.player2Tank.hp <= 0)
    {
        world.gameState = Player1Victory;
        return;
    }
}

void MatchSystem::CheckTimeoutVictory(World& world)
{
    // Match is still running.
    if (world.remainingTime > 0.0f)
    {
        return;
    }

    // Compare remaining HP when the timer expires.
    if (world.player1Tank.hp > world.player2Tank.hp)
    {
        world.gameState = Player1Victory;
    }
    else if (world.player2Tank.hp > world.player1Tank.hp)
    {
        world.gameState = Player2Victory;
    }
    else
    {
        world.gameState = Draw;
    }
}