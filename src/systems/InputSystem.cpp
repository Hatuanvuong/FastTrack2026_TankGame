#include "InputSystem.h"

#include <SDL3/SDL.h>
#include "../core/Constants.h"
#include "BulletSystem.h"

void InputSystem::Update(World& world, float deltaTime)
{
    // Update fire cooldown timers.
    world.player1Tank.fireCooldownTimer += deltaTime;
    world.player2Tank.fireCooldownTimer += deltaTime;

    // Get the current state of all keyboard keys.
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    // Redirect and move tank 1
    // Player 1
    if (keyboardState[SDL_SCANCODE_W])
    {
        // Calculate the tank's next position.
        world.player1Tank.direction = Up;
        const float nextY = world.player1Tank.y - world.player1Tank.speed * deltaTime;

        // Check Collision with BorderWall, ObstacleWall, OtherTank and apply next position
        if (CanMoveTo(world, world.player2Tank, world.player1Tank.x, nextY))
        {
            world.player1Tank.y = nextY;
        }
    }

    if (keyboardState[SDL_SCANCODE_S])
    {
        world.player1Tank.direction = Down;
        const float nextY = world.player1Tank.y + world.player1Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player2Tank, world.player1Tank.x, nextY))
        {
            world.player1Tank.y = nextY;
        }
    }

    if (keyboardState[SDL_SCANCODE_A])
    {
        world.player1Tank.direction = Left;
        const float nextX = world.player1Tank.x - world.player1Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player2Tank, nextX, world.player1Tank.y))
        {
            world.player1Tank.x = nextX;
        }
    }

    if (keyboardState[SDL_SCANCODE_D])
    {
        world.player1Tank.direction = Right;
        const float nextX = world.player1Tank.x + world.player1Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player2Tank, nextX, world.player1Tank.y))
        {
            world.player1Tank.x = nextX;
        }
    }

    // Redirect and move tank 2
    // Player 2
    if (keyboardState[SDL_SCANCODE_UP])
    {
        world.player2Tank.direction = Up;
        const float nextY = world.player2Tank.y - world.player2Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player1Tank, world.player2Tank.x, nextY))
        {
            world.player2Tank.y = nextY;
        }
    }

    if (keyboardState[SDL_SCANCODE_DOWN])
    {
        world.player2Tank.direction = Down;
        const float nextY = world.player2Tank.y + world.player2Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player1Tank, world.player2Tank.x, nextY))
        {
            world.player2Tank.y = nextY;
        }
    }

    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        world.player2Tank.direction = Left;
        const float nextX = world.player2Tank.x - world.player2Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player1Tank, nextX, world.player2Tank.y))
        {
            world.player2Tank.x = nextX;
        }
    }

    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        world.player2Tank.direction = Right;
        const float nextX = world.player2Tank.x + world.player2Tank.speed * deltaTime;

        if (CanMoveTo(world, world.player1Tank, nextX, world.player2Tank.y))
        {
            world.player2Tank.x = nextX;
        }
    }
}

void InputSystem::HandleFireInput(World& world,
                                  const SDL_Event& event,
                                  BulletSystem& bulletSystem)
{
    // Ignore non-keyboard events.
    if (event.type != SDL_EVENT_KEY_DOWN)
    {
        return;
    }

    // Player 1 fires a bullet using the Space key.
    if (event.key.scancode == SDL_SCANCODE_SPACE)
    {
        if (world.player1Tank.fireCooldownTimer >= Constants::FIRE_COOLDOWN)
        {
            bulletSystem.Fire(
            world.player1Bullets,
            world.player1Tank);

            // Reset the cooldown timer after firing.
            world.player1Tank.fireCooldownTimer = 0.0f;
        }
    }

    // Player 2 fires a bullet using the Enter key.
    if (event.key.scancode == SDL_SCANCODE_RETURN)
    {
        if (world.player2Tank.fireCooldownTimer >= Constants::FIRE_COOLDOWN)
        {
            bulletSystem.Fire(
                world.player2Bullets,
                world.player2Tank);

            // Reset the cooldown timer after firing.
            world.player2Tank.fireCooldownTimer = 0.0f;
        }
    }

}

bool InputSystem::IsMapCollision(const World& world,
                                 float nextX,
                                 float nextY) const
{
    // Identify the position of the left column.
    const int leftCol = static_cast<int>(nextX) / Constants::TILE_SIZE;

    // Identify the position of the right column.
    const int rightCol = static_cast<int>(nextX + Constants::TANK_SIZE - 1) / Constants::TILE_SIZE;

    // Identify the position of the top row.
    const int topRow = static_cast<int>(nextY) / Constants::TILE_SIZE;

    // Identify the position of the bottom row.
    const int bottomRow = static_cast<int>(nextY + Constants::TANK_SIZE - 1) / Constants::TILE_SIZE;

    // Check every tile covered by the tank. Includes tiles that are surrounded by the left column, right column, top row, and bottom row.
    for (int row = topRow; row <= bottomRow; ++row)
    {
        for (int col = leftCol; col <= rightCol; ++col)
        {
            // Prevent out of range map access.
            if (row < 0 || row >= Constants::MAP_ROWS || col < 0 || col >= Constants::MAP_COLS)
            {
                return true;
            }

            // Get tile type
            const TileType tile = world.map.GetTile(row, col);

            // Border walls and obstacle walls block movement.
            if (tile == BorderWall || tile == ObstacleWall)
            {
                return true;
            }
        }
    }

    return false;
}

bool InputSystem::IsTankCollision(const Tank& otherTank,
                                  float nextX,
                                  float nextY) const
{
    // Identify the information of rectangular tank player 1.
    SDL_FRect movingRect =
    {
        nextX,
        nextY,
        static_cast<float>(Constants::TANK_SIZE),
        static_cast<float>(Constants::TANK_SIZE)
    };

    // Identify the information of rectangular tank player 2.
    SDL_FRect otherRect =
    {
        otherTank.x,
        otherTank.y,
        static_cast<float>(Constants::TANK_SIZE),
        static_cast<float>(Constants::TANK_SIZE)
    };

    // Check the intersection of tank player 1 and tank player 2.
    return SDL_HasRectIntersectionFloat(&movingRect, &otherRect);
}

bool InputSystem::CanMoveTo(const World& world,
                            const Tank& otherTank,
                            float nextX,
                            float nextY) const
{
    // Checks whether the next position would collide with BorderWall, ObstacleWall
    if (IsMapCollision(world, nextX, nextY))
    {
        return false;
    }

    // Checks whether the next position would collide with another tank.
    if (IsTankCollision(otherTank, nextX, nextY))
    {
        return false;
    }

    return true;
}