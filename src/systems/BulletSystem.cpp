#include "BulletSystem.h"

void BulletSystem::Fire(std::vector<Bullet>& bullets, const Tank& tank)
{
    Bullet bullet;
    
    // Activate the newly created bullet.
    bullet.active = true;
    
    bullet.direction = tank.direction;
    bullet.owner = tank.playerId;
    
    // Spawn the bullet at the center of the tank.
    bullet.x = tank.x + Constants::TANK_SIZE * 0.5f - Constants::BULLET_SIZE * 0.5f;
    
    bullet.y = tank.y + Constants::TANK_SIZE * 0.5f - Constants::BULLET_SIZE * 0.5f;
    
    // Add the bullet to the player's bullet list.
    bullets.push_back(bullet);
}

void BulletSystem::Update(World& world, float deltaTime)
{
    // Update bullets fired by Player 1.
    for (Bullet& bullet : world.player1Bullets)
    {
        UpdateBullet(bullet, deltaTime);
    }

    // Update bullets fired by Player 2.
    for (Bullet& bullet : world.player2Bullets)
    {
        UpdateBullet(bullet, deltaTime);
}
}

void BulletSystem::UpdateBullet(Bullet& bullet, float deltaTime)
{
    // Inactive bullets do not need updating.
    if (!bullet.active)
    {
        return;
    }

    // Move the bullet based on its direction.
    switch (bullet.direction)
    {
    case Up:
        bullet.y -= bullet.speed * deltaTime;
        break;

    case Down:
        bullet.y += bullet.speed * deltaTime;
        break;

    case Left:
        bullet.x -= bullet.speed * deltaTime;
        break;

    case Right:
        bullet.x += bullet.speed * deltaTime;
        break;
    }
}