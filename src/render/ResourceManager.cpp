#include "ResourceManager.h"

#include <SDL3_image/SDL_image.h>

bool ResourceManager::Load(SDL_Renderer* renderer)
{
    m_borderWallTexture = IMG_LoadTexture(
        renderer,
        "assets/images/wall_border.png");

    if (!m_borderWallTexture)
    {
        SDL_Log("Failed to load wall_border.png");
        return false;
    }

    m_obstacleWallTexture = IMG_LoadTexture(
        renderer,
        "assets/images/wall_obstacle.png");

    if (!m_obstacleWallTexture)
    {
        SDL_Log("Failed to load wall_obstacle.png");
        return false;
    }

    m_blueTankTexture = IMG_LoadTexture(
        renderer,
        "assets/images/tank_blue.png");

    if (!m_blueTankTexture)
    {
        SDL_Log("Failed to load tank_blue.png");
        return false;
    }

    m_redTankTexture = IMG_LoadTexture(
        renderer,
        "assets/images/tank_red.png");

    if (!m_redTankTexture)
    {
        SDL_Log("Failed to load tank_red.png");
        return false;
    }

    return true;
}

void ResourceManager::Unload()
{
    SDL_DestroyTexture(m_borderWallTexture);
    SDL_DestroyTexture(m_obstacleWallTexture);
    SDL_DestroyTexture(m_blueTankTexture);
    SDL_DestroyTexture(m_redTankTexture);

    m_borderWallTexture = nullptr;
    m_obstacleWallTexture = nullptr;
    m_blueTankTexture = nullptr;
    m_redTankTexture = nullptr;
}

SDL_Texture* ResourceManager::GetBorderWallTexture() const
{
    return m_borderWallTexture;
}

SDL_Texture* ResourceManager::GetObstacleWallTexture() const
{
    return m_obstacleWallTexture;
}

SDL_Texture* ResourceManager::GetBlueTankTexture() const
{
    return m_blueTankTexture;
}

SDL_Texture* ResourceManager::GetRedTankTexture() const
{
    return m_redTankTexture;
}