#include "Game.h"

#include <SDL3/SDL.h>

#include "../core/Constants.h"

bool Game::Init()
{
    if (!m_renderer.Init())
    {
        return false;
    }

    m_gameState.player1 =
    {
        PlayerId::Player1,
        64.0f,
        64.0f,
        static_cast<float>(TANK_SIZE),
        static_cast<float>(TANK_SIZE),
        INITIAL_HP
    };

    m_gameState.player2 =
    {
        PlayerId::Player2,
        1120.0f,
        576.0f,
        static_cast<float>(TANK_SIZE),
        static_cast<float>(TANK_SIZE),
        INITIAL_HP
    };

    m_gameState.remainingTime = MATCH_DURATION_SECONDS;

    m_isRunning = true;

    return true;
}

void Game::Run()
{
    while (m_isRunning)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_isRunning = false;
            }
        }

        m_renderer.Render(m_gameState);
    }

    m_renderer.Shutdown();
}