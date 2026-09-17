#pragma once

#include <SDL3/SDL.h>

class ResourceManager
{
public:
    bool Load(SDL_Renderer* renderer);
    void Unload();

    SDL_Texture* GetBorderWallTexture() const;
    SDL_Texture* GetObstacleWallTexture() const;

    SDL_Texture* GetBlueTankTexture() const;
    SDL_Texture* GetRedTankTexture() const;

private:
    SDL_Texture* m_borderWallTexture{nullptr};
    SDL_Texture* m_obstacleWallTexture{nullptr};

    SDL_Texture* m_blueTankTexture{nullptr};
    SDL_Texture* m_redTankTexture{nullptr};
};