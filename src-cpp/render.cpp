#include "./SDL.h" //src\include\SDL.h
#include "./SDL_image.h"
#include <iostream>
#include <chrono>

#include "render.h"
#include "map.h"
#include "movement.h"

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
    window = SDL_CreateWindow("SDL Image Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_SHOWN);
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

//SDL
SDL_Event event;
SDL_Rect dstRect;
SDL_Texture* imageTexture1;
SDL_Texture* imageTexture2;
SDL_Texture* imageTextureW;
SDL_Texture* imageTextureA;
SDL_Texture* imageTextureS;
SDL_Texture* imageTextureD;

void CheckTextures() {
    if (!imageTexture1 || !imageTexture2) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }
    if (!imageTextureA) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }
    if (!imageTextureD) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }
    if (!imageTextureS) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return;
    }
    if (!imageTextureW) {
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
    SDL_DestroyTexture(imageTextureW);
    SDL_DestroyTexture(imageTextureA);
    SDL_DestroyTexture(imageTextureS);
    SDL_DestroyTexture(imageTextureD);
}

void Render::RenderLoop() {
    isRunning = true;

    // Load the images as textures
    imageTexture1 = IMG_LoadTexture(renderer, "src/Player-idle1.png");
    imageTexture2 = IMG_LoadTexture(renderer, "src/Player-idle2.png");

    imageTextureA = IMG_LoadTexture(renderer, "src/Player-a.png");
    imageTextureD = IMG_LoadTexture(renderer, "src/Player-d.png");
    imageTextureS = IMG_LoadTexture(renderer, "src/Player-s.png");
    imageTextureW = IMG_LoadTexture(renderer, "src/Player-w.png");

    CheckTextures();

    // Get the width and height of the textures
    
    SDL_QueryTexture(imageTexture1, NULL, NULL, &textureWidth, &textureHeight);

    dstRect = {SCREEN_WIDTH/16, SCREEN_HEIGHT/9, textureWidth, textureHeight};

    // Variables to control texture switching

    // Render loop
    while (isRunning) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            //make a function that checks the input for the keyboard to move the player texture/rectangle

            // SDL_Event event;
            // while(SDL_PollEvent(&event))
            // {
            //     switch(event.type)
            //     {
            //         case SDL_KEYDOWN:
            //             keyboard[event.key.keysym.sym] = false;
            //         break;
            //         case SDL_KEYUP:
            //             keyboard[event.key.keysym.sym] = true;
            //         break;
            //     }       
            // }
        }

        // Set background color
        Render::SetBackgroundColour(0,128,128,255);            // SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
        Map::DrawMap(renderer);
        Keyboard::ReadKeyboardInput();
        Movement::PlayerMove();
        Render::DeterminePlayerTexture();
        // DEBUG std::cout << "Player width: " << dstRect.w << " Player height: " << dstRect.h << std::endl;

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
