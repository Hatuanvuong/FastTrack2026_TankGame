#pragma once

#include "../game/World.h"

// Responsible for bullet spawning and movement.
class BulletSystem
{
public:
    // Creates a bullet from the specified tank.
    void Fire(std::vector<Bullet>& bullets, const Tank& tank);

    // Updates all active bullets.
    void Update(World& world, float deltaTime);

private:
    // Updates a single bullet.
    void UpdateBullet(Bullet& bullet, float deltaTime);
};