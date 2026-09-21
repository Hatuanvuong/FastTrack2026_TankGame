#include "InputSystem.h"

#include <SDL3/SDL.h>

void InputSystem::Update(World& world, float deltaTime)
{
    // Get the current state of all keyboard keys.
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    // Redirect and move tank 1
    // Player 1
    if (keyboardState[SDL_SCANCODE_W])
    {
        world.player1Tank.direction = Up;
        world.player1Tank.y -= world.player1Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_S])
    {
        world.player1Tank.direction = Down;
        world.player1Tank.y += world.player1Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_A])
    {
        world.player1Tank.direction = Left;
        world.player1Tank.x -= world.player1Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_D])
    {
        world.player1Tank.direction = Right;
        world.player1Tank.x += world.player1Tank.speed * deltaTime;
    }

    // Redirect and move tank 2
    // Player 2
    if (keyboardState[SDL_SCANCODE_UP])
    {
        world.player2Tank.direction = Up;
        world.player2Tank.y -= world.player2Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_DOWN])
    {
        world.player2Tank.direction = Down;
        world.player2Tank.y += world.player2Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        world.player2Tank.direction = Left;
        world.player2Tank.x -= world.player2Tank.speed * deltaTime;
    }

    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        world.player2Tank.direction = Right;
        world.player2Tank.x += world.player2Tank.speed * deltaTime;
    }
}