#include "src/include/SDL.h"
#include <iostream>

#include "render.h"


int main(int argc, char* argv[]) {
    if (Render::InitializeSDL() != 0) return 1;

    bool isRunning = true;
    SDL_Event event;
    
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

    Render::CleanUp();
    return 0;
}
