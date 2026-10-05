#include "BulletSystem.h"
#include <SDL3/SDL.h>

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
    // Ignore gameplay updates after the match ends.
    if (world.gameState != Playing)
    {
        return;
    }

    // Update bullets fired by Player 1.
    for (Bullet& bullet : world.player1Bullets)
    {
        UpdateBullet(world, bullet, deltaTime);
    }

    // Update bullets fired by Player 2.
    for (Bullet& bullet : world.player2Bullets)
    {
        UpdateBullet(world, bullet, deltaTime);
    }

    // Remove destroyed bullets fired by Player 1.
    RemoveInactiveBullets(world.player1Bullets);
    
    // Remove destroyed bullets fired by Player 2.
    RemoveInactiveBullets(world.player2Bullets);
}

void BulletSystem::UpdateBullet(World& world, Bullet& bullet, float deltaTime)
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

    // Destroy the bullet when it hits a wall.
    if (IsMapCollision(world, bullet))
    {
        bullet.active = false;
        return;
    }

    // Player 1 bullets can only hit Player 2.
    if (bullet.owner == Player1)
    {
        if (IsTankCollision(bullet, world.player2Tank))
        {
            world.player2Tank.hp -= Constants::BULLET_DAMAGE;
    
            if (world.player2Tank.hp < 0)
            {
                world.player2Tank.hp = 0;
            }
    
            bullet.active = false;
            return;
        }
    }

    // Player 2 bullets can only hit Player 1.
    if (bullet.owner == Player2)
    {
        if (IsTankCollision(bullet, world.player1Tank))
        {
            world.player1Tank.hp -= Constants::BULLET_DAMAGE;
    
            if (world.player1Tank.hp < 0)
            {
                world.player1Tank.hp = 0;
            }
    
            bullet.active = false;
            return;
        }
    }
}

bool BulletSystem::IsMapCollision(const World& world, const Bullet& bullet) const
{
    // Identify the position of the left column.
    const int leftCol = static_cast<int>(bullet.x) / Constants::TILE_SIZE;

    // Identify the position of the right column.
    const int rightCol = static_cast<int>(bullet.x + Constants::BULLET_SIZE - 1) / Constants::TILE_SIZE;

    // Identify the position of the top row.
    const int topRow = static_cast<int>(bullet.y) / Constants::TILE_SIZE;

    // Identify the position of the bottom row.
    const int bottomRow = static_cast<int>(bullet.y + Constants::BULLET_SIZE - 1) / Constants::TILE_SIZE;

    // Check every tile covered by the bullet. Includes tiles that are surrounded by the left column, right column, top row, and bottom row.
    for (int row = topRow; row <= bottomRow; ++row)
    {
        for (int col = leftCol; col <= rightCol; ++col)
        {
            if (row < 0 || row >= Constants::MAP_ROWS || col < 0 || col >= Constants::MAP_COLS)
            {
                return true;
            }

            TileType tile = world.map.GetTile(row, col);

            if (tile == BorderWall || tile == ObstacleWall)
            {
                return true;
            }
        }
    }

    return false;
}

bool BulletSystem::IsTankCollision(const Bullet& bullet, const Tank& tank) const
{
    // Identify the information of rectangular bullet.
    SDL_FRect bulletRect =
    {
        bullet.x,
        bullet.y,
        static_cast<float>(Constants::BULLET_SIZE),
        static_cast<float>(Constants::BULLET_SIZE)
    };

    // Identify the information of rectangular tank.
    SDL_FRect tankRect =
    {
        tank.x,
        tank.y,
        static_cast<float>(Constants::TANK_SIZE),
        static_cast<float>(Constants::TANK_SIZE)
    };

    // Check the intersection of tank bullet and tank.
    return SDL_HasRectIntersectionFloat(&bulletRect, &tankRect);
}

void BulletSystem::RemoveInactiveBullets(std::vector<Bullet>& bullets)
{
    for (auto it = bullets.begin();
         it != bullets.end();)
    {
        // Remove bullets that have been destroyed.
        if (!it->active)
        {
            it = bullets.erase(it);
        }
        else
        {
            // Move to the next bullet.
            ++it;
        }
    }
}