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
    void UpdateBullet(World& world, Bullet& bullet, float deltaTime);

    // Checks whether the bullet collides with BorderWall or ObstacleWall.
    bool IsMapCollision(const World& world, const Bullet& bullet) const;
    
    // Checks whether the bullet collides with a tank.
    bool IsTankCollision(const Bullet& bullet, const Tank& tank) const;

    // Removes destroyed bullets from a bullet list.
    void RemoveInactiveBullets(std::vector<Bullet>& bullets);
};