#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game/World.h"
#include "render/Renderer.h"

int main()
{
    // Initialize the SDL video subsystem.
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }

    // Initialize SDL_ttf for HUD text rendering.
    if (!TTF_Init())
    {
        SDL_Quit();
        return -1;
    }

    // Create the initial game world.
    World world;

    // Create the renderer responsible for drawing the game world.
    Renderer renderer;

    // Create the SDL window, renderer and load resources.
    if (!renderer.Initialize())
    {
        TTF_Quit();
        SDL_Quit();

        return -1;
    }

    // Controls the main application loop.
    bool isRunning = true;

    SDL_Event event;

    // Main application loop.
    while (isRunning)
    {
        // Process all pending SDL events.
        while (SDL_PollEvent(&event))
        {
            // Exit the application when the window close button is pressed.
            if (event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }
        }

        // Render the current game state.
        renderer.Render(world);
    }

    // Release all renderer resources.
    renderer.Shutdown();

    // Shut down SDL_ttf.
    TTF_Quit();

    // Shut down all SDL subsystems.
    SDL_Quit();

    return 0;
}