#include "Map.h"

Map::Map()
{
    CreateBorderWalls();
    CreateObstacleWalls();
}

void Map::CreateBorderWalls()
{
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            if (row == 0 ||
                row == MAP_ROWS - 1 ||
                col == 0 ||
                col == MAP_COLS - 1)
            {
                m_tiles[row][col] = TileType::BorderWall;
            }
            else
            {
                m_tiles[row][col] = TileType::Empty;
            }
        }
    }
}

void Map::CreateObstacleWalls()
{
    for (int col = 10; col < 16; ++col)
    {
        m_tiles[5][col] = TileType::ObstacleWall;
    }

    for (int col = 24; col < 30; ++col)
    {
        m_tiles[5][col] = TileType::ObstacleWall;
    }

    for (int col = 18; col < 22; ++col)
    {
        m_tiles[10][col] = TileType::ObstacleWall;
    }
}

TileType Map::GetTile(int row, int col) const
{
    return m_tiles[row][col];
}