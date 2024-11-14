#include "src/include/SDL.h"
#include "src/include/SDL_image.h"
#include <iostream>
#include <chrono>

#include "render.h"

// Define global SDL pointers
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int Render::InitializeSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_image for PNG support
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create SDL window
    window = SDL_CreateWindow("SDL Image Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL Window Creation Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    return 0; // success
}

bool isRunning;
bool showImage1 = true;
int textureWidth, textureHeight;
int toggleInterval;
//SDL
SDL_Event event;
SDL_Rect dstRect;
SDL_Texture* imageTexture1;
SDL_Texture* imageTexture2;

void CheckTextures() {
    if (!imageTexture1 || !imageTexture2) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }
}

void Render::SetBackgroundColour(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
    SDL_RenderClear(renderer);
}

void Render::FreeTextures() {
    SDL_DestroyTexture(imageTexture1);
    SDL_DestroyTexture(imageTexture2);
}

void Render::RenderLoop() {
    isRunning = true;

    // Load the images as textures
    imageTexture1 = IMG_LoadTexture(renderer, "src/Player-idle.png");
    imageTexture2 = IMG_LoadTexture(renderer, "src/Player-idle.png");

    CheckTextures();

    // Get the width and height of the textures
    
    SDL_QueryTexture(imageTexture1, NULL, NULL, &textureWidth, &textureHeight);

    dstRect = {100, 100, textureWidth, textureHeight};

    // Variables to control texture switching
    auto lastToggleTime = std::chrono::high_resolution_clock::now();
    toggleInterval = 500; // milliseconds

    // Render loop
    while (isRunning) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Calculate elapsed time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastToggleTime).count();

        // Toggle between textures based on the interval
        if (elapsedTime >= toggleInterval) {
            showImage1 = !showImage1;
            lastToggleTime = currentTime; // reset the timer
        }

        // Set background color
        Render::SetBackgroundColour(0,128,128,255);            // SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);

        // Render the appropriate texture based on `showImage1`
        if (showImage1) {
            SDL_RenderCopy(renderer, imageTexture1, NULL, &dstRect);
        } else {
            SDL_RenderCopy(renderer, imageTexture2, NULL, &dstRect);
        }

        // Present the rendered content on the screen
        SDL_RenderPresent(renderer);
    }

    // Free textures once we're done
    Render::FreeTextures();
}

void Render::CleanUp() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
