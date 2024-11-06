#include "src/include/SDL.h"
#include "src/include/SDL_image.h"
#include <iostream>

#include "render.h"

// Define global SDL pointers
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int Render::InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    window = SDL_CreateWindow("SDL Image Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);
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

    // Load the image as a texture
    SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "src/png-transparent-spider-man-heroes-download-with-transparent-background-free-thumbnail.png");
    if (!imageTexture) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }

    // Get the width and height of the texture for positioning
    int textureWidth, textureHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &textureWidth, &textureHeight);

    // Define a destination rectangle where the texture will be drawn on the screen
    SDL_Rect dstRect = {100, 100, textureWidth, textureHeight};

    // Render loop
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

        // Render the image texture to the screen
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

        // Present the rendered content on the screen
        SDL_RenderPresent(renderer);
    }

    // Free the texture once we're done with it
    SDL_DestroyTexture(imageTexture);
}

void Render::CleanUp() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    } 
    if (window) {
        SDL_DestroyWindow(window);
    } 
    
    IMG_Quit();
    SDL_Quit();
}
