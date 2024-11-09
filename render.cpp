#include "src/include/SDL.h"
#include "src/include/SDL_image.h"
#include <iostream>
#include <chrono>

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
bool showImage1 = true;
SDL_Event event;

void Render::RenderLoop() {
    isRunning = true;

    // Load the images as textures
    SDL_Texture* imageTexture1 = IMG_LoadTexture(renderer, "src/png-transparent-spider-man-heroes-download-with-transparent-background-free-thumbnail.png");
    SDL_Texture* imageTexture2 = IMG_LoadTexture(renderer, "src/images.jpg");

    if (!imageTexture1 || !imageTexture2) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }

    // Get the width and height of the textures
    int textureWidth, textureHeight;
    SDL_QueryTexture(imageTexture1, NULL, NULL, &textureWidth, &textureHeight);

    SDL_Rect dstRect = {100, 100, textureWidth, textureHeight};

    // Variables to control texture switching
    auto lastToggleTime = std::chrono::high_resolution_clock::now();
    int toggleInterval = 500; // milliseconds

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
        SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
        SDL_RenderClear(renderer);

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
    SDL_DestroyTexture(imageTexture1);
    SDL_DestroyTexture(imageTexture2);
}

void Render::CleanUp() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
