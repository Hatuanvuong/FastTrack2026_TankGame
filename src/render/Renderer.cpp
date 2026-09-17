#include "Renderer.h"

#include "../core/Constants.h"

#include "../core/Tile.h"

bool Renderer::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL");
        return false;
    }

    m_window = SDL_CreateWindow(
        "Tank Battle PvP",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!m_window)
    {
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        nullptr);

    if (!m_renderer)
    {
        return false;
    }

    return m_resourceManager.Load(m_renderer);
}

void Renderer::DrawMap(const Map& map)
{
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            SDL_Texture* texture = nullptr;

            switch (map.GetTile(row, col))
            {
                case TileType::BorderWall:
                    texture = m_resourceManager.GetBorderWallTexture();
                    break;

                case TileType::ObstacleWall:
                    texture = m_resourceManager.GetObstacleWallTexture();
                    break;

                default:
                    break;
            }

            if (!texture)
            {
                continue;
            }

            SDL_FRect destinationRect
            {
                static_cast<float>(col * TILE_SIZE),
                static_cast<float>(HUD_HEIGHT + row * TILE_SIZE),
                static_cast<float>(TILE_SIZE),
                static_cast<float>(TILE_SIZE)
            };

            SDL_RenderTexture(
                m_renderer,
                texture,
                nullptr,
                &destinationRect);
        }
    }
}

void Renderer::DrawTank(const Tank& tank)
{
    SDL_Texture* texture = nullptr;

    if (tank.owner == PlayerId::Player1)
    {
        texture = m_resourceManager.GetBlueTankTexture();
    }
    else
    {
        texture = m_resourceManager.GetRedTankTexture();
    }

    SDL_FRect destinationRect
    {
        tank.x,
        tank.y + static_cast<float>(HUD_HEIGHT),
        tank.width,
        tank.height
    };

    SDL_RenderTexture(
        m_renderer,
        texture,
        nullptr,
        &destinationRect);
}

void Renderer::DrawHud(const GameState& gameState)
{
    // Draw HUD background

    SDL_SetRenderDrawColor(
        m_renderer,
        60,
        60,
        60,
        255);

    SDL_FRect hudRect
    {
        0.0f,
        0.0f,
        static_cast<float>(WINDOW_WIDTH),
        static_cast<float>(HUD_HEIGHT)
    };

    SDL_RenderFillRect(
        m_renderer,
        &hudRect);

    // Draw HP bars

    SDL_SetRenderDrawColor(
        m_renderer,
        0,
        255,
        0,
        255);

    SDL_FRect player1HpBar
    {
        20.0f,
        20.0f,
        static_cast<float>(gameState.player1.hp * 2),
        20.0f
    };

    SDL_FRect player2HpBar
    {
        1060.0f,
        20.0f,
        static_cast<float>(gameState.player2.hp * 2),
        20.0f
    };

    SDL_RenderFillRect(
        m_renderer,
        &player1HpBar);

    SDL_RenderFillRect(
        m_renderer,
        &player2HpBar);
}

void Renderer::Render(const GameState& gameState)
{
    SDL_SetRenderDrawColor(
        m_renderer,
        40,
        40,
        40,
        255);

    SDL_RenderClear(m_renderer);

    DrawMap(gameState.map);
    DrawTank(gameState.player1);
    DrawTank(gameState.player2);
    DrawHud(gameState);

    SDL_RenderPresent(m_renderer);
}

void Renderer::Shutdown()
{
    m_resourceManager.Unload();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    m_renderer = nullptr;
    m_window = nullptr;

    SDL_Quit();
}