#include "src/include/SDL.h"
#include <iostream>

#include "render.h"

// Define global SDL pointers
SDL_Window* window = nullptr;    // Define the variables here
SDL_Renderer* renderer = nullptr; // Define the variables here

int Render::InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    window = SDL_CreateWindow("SDL Button Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    return 0;
}

bool isRunning;
SDL_Event event;

void Render::RenderLoop() {
    isRunning = true;
    
    while (isRunning) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Set background color
        SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255); // Teal
        SDL_RenderClear(renderer);

        // Draw the button with different color if hovered

        // Present the rendered content
        SDL_RenderPresent(renderer);
    }
}

void Render::CleanUp() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}