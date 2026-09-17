#pragma once

namespace Constants
{
    // Window
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 768;

    // HUD
    const int HUD_HEIGHT = 64;

    // Map
    const int MAP_WIDTH = 1280;
    const int MAP_HEIGHT = 704;
    const int MAP_ROWS = 22;
    const int MAP_COLS = 40;

    // Tile
    const int TILE_SIZE = 32;

    // Tank
    const int TANK_SIZE = 64;
    const int TANK_HP = 100;
    const float TANK_SPEED = 200.0f;

    // Tank Spawn Position
    const float PLAYER1_SPAWN_X = 64.0f;
    const float PLAYER1_SPAWN_Y = 64.0f;
    const float PLAYER2_SPAWN_X = 1120.0f;
    const float PLAYER2_SPAWN_Y = 576.0f;

    // Bullet
    const int BULLET_SIZE = 8;
    const int BULLET_DAMAGE = 5;
    const float BULLET_SPEED = 500.0f;

    // Fire
    const float FIRE_COOLDOWN = 0.3f; // 300 ms

    // Match
    const int MATCH_DURATION_SECONDS = 300;
}