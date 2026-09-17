#pragma once

constexpr int TILE_SIZE = 32;

constexpr int MAP_ROWS = 22;

constexpr int MAP_COLS = 40;

constexpr int MAP_WIDTH = MAP_COLS * TILE_SIZE;

constexpr int MAP_HEIGHT = MAP_ROWS * TILE_SIZE;

constexpr int HUD_HEIGHT = 64;

constexpr int WINDOW_WIDTH = MAP_WIDTH;

constexpr int WINDOW_HEIGHT = HUD_HEIGHT + MAP_HEIGHT;

constexpr int TANK_SIZE = 64;

constexpr int INITIAL_HP = 100;

constexpr int MATCH_DURATION_SECONDS = 300;