#pragma once

#include "Constants.h"
#include "Tile.h"

class Map
{
public:
    Map();

    TileType GetTile(int row, int col) const;

private:
    TileType m_tiles[MAP_ROWS][MAP_COLS]{};

    void CreateBorderWalls();
    void CreateObstacleWalls();
};