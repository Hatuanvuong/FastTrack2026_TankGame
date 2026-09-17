#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "../game/World.h"

// Responsible for rendering the game world.
class Renderer
{
public:
    Renderer();

    ~Renderer();

    // Creates SDL window, renderer and loads resources.
    bool Initialize();

    // Releases all SDL resources.
    void Shutdown();

    // Draws the current game world.
    void Render(const World& world);

private:
    // Loads textures and fonts used in Phase 1.
    bool LoadResources();

    // Draws the HUD area.
    void DrawHud();

    // Draws all map tiles.
    void DrawMap(const Map& map);

    // Draws a tank.
    void DrawTank(const Tank& tank);

private:
    // Main application window.
    SDL_Window* m_window;

    // SDL renderer used for drawing.
    SDL_Renderer* m_renderer;

    // Map textures.
    SDL_Texture* m_borderWallTexture;
    SDL_Texture* m_obstacleWallTexture;

    // Tank textures.
    SDL_Texture* m_player1TankTexture;
    SDL_Texture* m_player2TankTexture;

    // Font used to render HUD text.
    TTF_Font* m_hudFont;
};