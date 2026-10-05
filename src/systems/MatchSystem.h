#pragma once

#include "../game/World.h"

// Responsible for match timer and victory rules.
class MatchSystem
{
public:
    // Updates match state.
    void Update(World& world, float deltaTime);

    // Restarts the match.
    void Restart(World& world);

private:
    // Updates remaining match time.
    void UpdateTimer(World& world, float deltaTime);

    // Checks HP victory conditions.
    void CheckHpVictory(World& world);

    // Checks timeout victory conditions.
    void CheckTimeoutVictory(World& world);
};