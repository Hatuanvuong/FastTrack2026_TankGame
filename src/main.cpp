#include <SDL3/SDL.h>

int main(int argc, char* argv[])
{
    // Initialize SDL video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    // Create application window
    SDL_Window* window = SDL_CreateWindow(
        "FastTrack2026 Tank Game",
        1280,
        720,
        0);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());

        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, nullptr);

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s",
                SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        return -1;
    }

    bool running = true;

    while (running)
    {
        SDL_Event event;

        // Process events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        // Background color
        SDL_SetRenderDrawColor(
            renderer,
            30,
            60,
            120,
            255);

        SDL_RenderClear(renderer);

        // Draw a rectangle as tank placeholder
        SDL_FRect tank =
        {
            200.0f,
            200.0f,
            64.0f,
            64.0f
        };

        SDL_SetRenderDrawColor(
            renderer,
            0,
            0,
            255,
            255);

        SDL_RenderFillRect(
            renderer,
            &tank);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}