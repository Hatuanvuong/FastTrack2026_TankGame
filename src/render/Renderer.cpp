#include "Renderer.h"

#include <SDL3_image/SDL_image.h>

#include "../core/Constants.h"
#include "../core/PlayerId.h"
#include "../core/TileType.h"
#include <sstream>
#include <iomanip>
#include <string>

Renderer::Renderer()
{
    // Initialize all pointers to nullptr.
    m_window = nullptr;
    m_renderer = nullptr;

    m_borderWallTexture = nullptr;
    m_obstacleWallTexture = nullptr;

    m_player1TankTexture = nullptr;
    m_player2TankTexture = nullptr;

    m_bulletTexture = nullptr;

    m_hudFont = nullptr;
}

Renderer::~Renderer()
{
    Shutdown();
}

bool Renderer::Initialize()
{
    // Create the main SDL window.
    m_window = SDL_CreateWindow(
        "Tank Battle PvP",
        Constants::WINDOW_WIDTH,
        Constants::WINDOW_HEIGHT,
        0);

    if (m_window == nullptr)
    {
        return false;
    }

    // Create the SDL renderer.
    // SDL_Renderer is responsible for:
    // - Drawing textures
    // - Drawing rectangles
    // - Drawing lines
    // - Presenting frames to the screen
    m_renderer = SDL_CreateRenderer(m_window, nullptr);

    if (m_renderer == nullptr)
    {
        return false;
    }

    // Load all textures and fonts required.
    return LoadResources();
}

bool Renderer::LoadResources()
{
    // Load border wall texture from PNG file.
    m_borderWallTexture = IMG_LoadTexture(
        m_renderer,
        "assets/images/map/border_wall.png");

    if (m_borderWallTexture == nullptr)
    {
        return false;
    }

    // Load obstacle wall texture from PNG file.
    m_obstacleWallTexture = IMG_LoadTexture(
        m_renderer,
        "assets/images/map/obstacle_wall.png");

    if (m_obstacleWallTexture == nullptr)
    {
        return false;
    }

    // Load Player 1 tank texture from PNG file.
    m_player1TankTexture = IMG_LoadTexture(
        m_renderer,
        "assets/images/tank/player1_tank.png");

    if (m_player1TankTexture == nullptr)
    {
        return false;
    }

    // Load Player 2 tank texture from PNG file.
    m_player2TankTexture = IMG_LoadTexture(
        m_renderer,
        "assets/images/tank/player2_tank.png");

    if (m_player2TankTexture == nullptr)
    {
        return false;
    }

    // Load Bullet texture from PNG file.
    m_bulletTexture = IMG_LoadTexture(
        m_renderer,
        "assets/images/bullet/bullet.png");
        
    if (m_bulletTexture == nullptr)
    {
        return false;
    }

    // Open the font used to render HUD text.
    // Parameters:
    // - File path
    // - Font size
    m_hudFont = TTF_OpenFont(
        "assets/fonts/NotoSans-Regular.ttf",
        24);

    if (m_hudFont == nullptr)
    {
        return false;
    }

    return true;
}

void Renderer::Shutdown()
{
    // Release font resource created by TTF_OpenFont().
    if (m_hudFont != nullptr)
    {
        TTF_CloseFont(m_hudFont);
        m_hudFont = nullptr;
    }

    // Release tank textures.
    if (m_player2TankTexture != nullptr)
    {
        SDL_DestroyTexture(m_player2TankTexture);
        m_player2TankTexture = nullptr;
    }

    if (m_player1TankTexture != nullptr)
    {
        SDL_DestroyTexture(m_player1TankTexture);
        m_player1TankTexture = nullptr;
    }

    // Release map textures.
    if (m_obstacleWallTexture != nullptr)
    {
        SDL_DestroyTexture(m_obstacleWallTexture);
        m_obstacleWallTexture = nullptr;
    }

    if (m_borderWallTexture != nullptr)
    {
        SDL_DestroyTexture(m_borderWallTexture);
        m_borderWallTexture = nullptr;
    }

    // Release bullet textures.
    if (m_bulletTexture != nullptr)
    {
        SDL_DestroyTexture(m_bulletTexture);
        m_bulletTexture = nullptr;
    }

    // Release SDL renderer.
    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    // Release SDL window.
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Renderer::Render(const World& world)
{
    // Set the color used when clearing the frame.
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);

    // Clear the previous frame.
    SDL_RenderClear(m_renderer);

    // Draw objects in render order.
    DrawHud(world);

    DrawMap(world.map);

    DrawTank(world.player1Tank);
    DrawTank(world.player2Tank);

    // Render all active bullets fired by Player 1.
    for (const Bullet& bullet : world.player1Bullets)
    {
        DrawBullet(bullet);
    }

    // Render all active bullets fired by Player 2.
    for (const Bullet& bullet : world.player2Bullets)
    {
        DrawBullet(bullet);
    }

    // Draws game over overlay.
    if (world.gameState != Playing)
    {
        DrawGameOverScreen(world);
    }

    // Display the completed frame on screen.
    // Everything rendered before this call is stored in the back buffer.
    SDL_RenderPresent(m_renderer);
}

void Renderer::DrawHud(const World& world)
{
    // Set the color used by SDL_RenderFillRect().
    SDL_SetRenderDrawColor(m_renderer, 70, 70, 70, 255);

    SDL_FRect hudRect =
    {
        0.0f,
        0.0f,
        static_cast<float>(Constants::WINDOW_WIDTH),
        static_cast<float>(Constants::HUD_HEIGHT)
    };

    // Draw a filled rectangle used as HUD background.
    SDL_RenderFillRect(m_renderer, &hudRect);

    // Convert the remaining match time from seconds to MM:SS format.
    int totalSeconds = static_cast<int>(world.remainingTime);

    int minutes = totalSeconds / 60;

    int seconds = totalSeconds % 60;

    // Build the HUD text using the current HP values and remaining match time.
    std::ostringstream textStream;

    textStream
        << "P1 HP: "
        << world.player1Tank.hp
        << "      TIME: "
        << std::setw(2)
        << std::setfill('0')
        << minutes
        << ":"
        << std::setw(2)
        << std::setfill('0')
        << seconds
        << "      P2 HP: "
        << world.player2Tank.hp;

    std::string hudText = textStream.str();

    // White color used for HUD text.
    SDL_Color textColor = {255, 255, 255, 255};

    // Render text into an SDL_Surface.
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(
            m_hudFont,
            hudText.c_str(),
            0,
            textColor);

    if (textSurface == nullptr)
    {
        return;
    }

    // Convert the surface into a texture.
    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(m_renderer, textSurface);

    if (textTexture == nullptr)
    {
        SDL_DestroySurface(textSurface);
        return;
    }

    // Position the HUD text inside the HUD background area.
    SDL_FRect textRect =
    {
        20.0f,
        18.0f,
        static_cast<float>(textSurface->w),
        static_cast<float>(textSurface->h)
    };

    // Render the generated text.
    SDL_RenderTexture(
        m_renderer,
        textTexture,
        nullptr,
        &textRect);

    // Release temporary text resources.
    SDL_DestroyTexture(textTexture);
    SDL_DestroySurface(textSurface);
}

void Renderer::DrawMap(const Map& map)
{
    // Draw every visible tile in the map.
    for (int row = 0; row < map.GetRows(); ++row)
    {
        for (int col = 0; col < map.GetCols(); ++col)
        {
            TileType tileType = map.GetTile(row, col);

            SDL_Texture* texture = nullptr;

            // Select the appropriate texture based on tile type.
            if (tileType == BorderWall)
            {
                texture = m_borderWallTexture;
            }
            else if (tileType == ObstacleWall)
            {
                texture = m_obstacleWallTexture;
            }

            // Empty tiles do not need rendering.
            if (texture == nullptr)
            {
                continue;
            }

            SDL_FRect tileRect =
            {
                static_cast<float>(col * Constants::TILE_SIZE),

                static_cast<float>(
                    row * Constants::TILE_SIZE +
                    Constants::HUD_HEIGHT),

                static_cast<float>(Constants::TILE_SIZE),
                static_cast<float>(Constants::TILE_SIZE)
            };

            // Draw the tile texture at its destination rectangle.
            SDL_RenderTexture(
                m_renderer,
                texture,
                nullptr,
                &tileRect);
        }
    }
}

void Renderer::DrawTank(const Tank& tank)
{
    SDL_Texture* texture = nullptr;

    // Select tank texture based on player ownership.
    if (tank.playerId == Player1)
    {
        texture = m_player1TankTexture;
    }
    else
    {
        texture = m_player2TankTexture;
    }

    // Convert the tank facing direction to an SDL rotation angle.
    // The tank texture is designed to face Up by default (0 degrees).
    double angle = 0.0;

    switch (tank.direction)
    {
    // Render the texture at 0 degrees.
    case Up:
        angle = 0.0;
        break;
    
    // Render the texture at 90 degrees.
    case Right:
        angle = 90.0;
        break;

    // Render the texture at 180 degrees.
    case Down:
        angle = 180.0;
        break;

    // Render the texture at 270 degrees.
    case Left:
        angle = 270.0;
        break;
    }

    SDL_FRect tankRect =
    {
        tank.x,

        // Offset tank position by HUD height so that
        // tanks are rendered inside the map area.
        tank.y + Constants::HUD_HEIGHT,
        
        static_cast<float>(Constants::TANK_SIZE),
        static_cast<float>(Constants::TANK_SIZE)
    };

    // Render the tank using the current rotation angle.
    SDL_RenderTextureRotated(
        m_renderer,
        texture,
        nullptr,
        &tankRect,
        angle,
        nullptr,
        SDL_FLIP_NONE);
}

void Renderer::DrawBullet(const Bullet& bullet)
{
    // Inactive bullets do not need rendering.
    if (!bullet.active)
    {
        return;
    }

    SDL_FRect bulletRect =
    {
        bullet.x,

        // Offset bullet position by HUD height so that bullets are rendered inside the map area.
        bullet.y + Constants::HUD_HEIGHT,

        static_cast<float>(Constants::BULLET_SIZE),
        static_cast<float>(Constants::BULLET_SIZE)
    };

    // Draw the bullet texture at its destination rectangle.
    SDL_RenderTexture(
        m_renderer,
        m_bulletTexture,
        nullptr,
        &bulletRect);
}

void Renderer::DrawGameOverScreen(const World& world)
{
    // Draw a semi-transparent black overlay.
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(
        m_renderer,
        0,
        0,
        0,
        180);

    SDL_FRect overlay =
    {
        0.0f,
        0.0f,
        static_cast<float>(Constants::WINDOW_WIDTH),
        static_cast<float>(Constants::WINDOW_HEIGHT)
    };

    SDL_RenderFillRect(m_renderer, &overlay);

    std::string text;

    // Select the match result text.
    if (world.gameState == Player1Victory)
    {
        text = "PLAYER 1 WINS - PRESS R TO RESTART";
    }
    else if (world.gameState == Player2Victory)
    {
        text = "PLAYER 2 WINS - PRESS R TO RESTART";
    }
    else if (world.gameState == Draw)
    {
        text = "DRAW - PRESS R TO RESTART";
    }
    else
    {
        return;
    }

    SDL_Color textColor =
    {
        255,
        255,
        255,
        255
    };

    // Render the result text into a surface.
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(
            m_hudFont,
            text.c_str(),
            0,
            textColor);

    if (textSurface == nullptr)
    {
        return;
    }

    // Convert the surface into a texture.
    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(
            m_renderer,
            textSurface);

    if (textTexture == nullptr)
    {
        SDL_DestroySurface(textSurface);
        return;
    }

    SDL_FRect textRect =
    {
        (Constants::WINDOW_WIDTH - textSurface->w) * 0.5f,

        (Constants::WINDOW_HEIGHT - textSurface->h) * 0.5f,

        static_cast<float>(textSurface->w),
        static_cast<float>(textSurface->h)
    };

    // Draw the result text at the center of the screen.
    SDL_RenderTexture(
        m_renderer,
        textTexture,
        nullptr,
        &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_DestroySurface(textSurface);
}