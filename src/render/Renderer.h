#pragma once

#include <SDL3/SDL.h>

#include "../core/GameState.h"
#include "ResourceManager.h"

class Renderer
{
public:
    bool Init();
    void Render(const GameState& gameState);
    void Shutdown();

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};

    ResourceManager m_resourceManager;

    void DrawMap(const Map& map);
    void DrawTank(const Tank& tank);
    void DrawHud(const GameState& gameState);
};