#pragma once

#include "../core/GameState.h"
#include "../render/Renderer.h"

class Game
{
public:
    bool Init();
    void Run();

private:
    bool m_isRunning{false};

    GameState m_gameState;
    Renderer m_renderer;
};