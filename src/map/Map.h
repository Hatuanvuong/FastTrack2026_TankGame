#pragma once

#include "../core/Constants.h"
#include "../core/TileType.h"

// Represents the game map.
class Map
{
public:
    Map();

    // Returns the tile type at the given grid position.
    TileType GetTile(int row, int col) const;

    // Returns the number of rows in the map.
    int GetRows() const;

    // Returns the number of columns in the map.
    int GetCols() const;

private:
    // Initializes map data from the predefined layout.
    void Initialize();

private:
    // Runtime tile data used by the game.
    TileType m_tiles[Constants::MAP_ROWS][Constants::MAP_COLS];
};