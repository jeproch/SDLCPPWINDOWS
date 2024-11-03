#include "src/include/SDL.h"
#include <iostream>

// Define global SDL pointers
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Define the button's rectangle
SDL_Rect buttonRect = {500, 250, 200, 100}; // Position and size of the button

int InitializeSDL() {
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

void CleanUp() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

bool IsMouseInsideButton(int mouseX, int mouseY) {
    return mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w &&
           mouseY > buttonRect.y && mouseY < buttonRect.y + buttonRect.h;
}

int main(int argc, char* argv[]) {
    if (InitializeSDL() != 0) return 1;

    bool isRunning = true;
    SDL_Event event;
    bool buttonHovered = false;
    
    while (isRunning) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if the mouse is inside the button area
                buttonHovered = IsMouseInsideButton(mouseX, mouseY);

                // Handle mouse click on the button
                if (buttonHovered && event.type == SDL_MOUSEBUTTONDOWN) {
                    std::cout << "Button clicked!" << std::endl;
                }
            }
        }

        // Set background color
        SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255); // Teal
        SDL_RenderClear(renderer);

        // Draw the button with different color if hovered
        if (buttonHovered) {
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // Red for hover
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        }
        SDL_RenderFillRect(renderer, &buttonRect);

        // Present the rendered content
        SDL_RenderPresent(renderer);
    }

    CleanUp();
    return 0;
}
