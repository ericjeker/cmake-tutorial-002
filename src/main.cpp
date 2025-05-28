#include <SDL3/SDL.h>
#include <iostream>
#include <string>


void logSDLInfo() {
    std::cout << "=== SDL3 Debug Information ===" << std::endl;

    // Get SDL version
    const auto version = SDL_GetVersion();
    std::cout << "Compiled SDL Version: " << version << std::endl;

    // Get platform info
    std::cout << "Platform: " << SDL_GetPlatform() << std::endl;

    // Get available video drivers
    int num_drivers = SDL_GetNumVideoDrivers();
    std::cout << "Available video drivers (" << num_drivers << "):" << std::endl;
    for (int i = 0; i < num_drivers; ++i) {
        std::cout << "  " << i << ": " << SDL_GetVideoDriver(i) << std::endl;
    }

    std::cout << "===============================" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "Starting SDL3 application..." << std::endl;

    // Log SDL info before initialization
    logSDLInfo();

    // Clear any existing error
    SDL_ClearError();

    std::cout << "Attempting to initialize SDL with VIDEO subsystem..." << std::endl;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a Window
    SDL_Window* window = SDL_CreateWindow("Hello SDL!", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    if (const SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr); !renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Event Loop (Keeps the window open until user closes it)
    bool keepRunning = true;
    SDL_Event event;
    while (keepRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                keepRunning = false;
            }
        }

        // Simple screen coloring (optional)
        SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0, 0, 0, 255); // Black
        SDL_RenderClear(SDL_GetRenderer(window));
        SDL_RenderPresent(SDL_GetRenderer(window));
    }

    // Clean up resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
