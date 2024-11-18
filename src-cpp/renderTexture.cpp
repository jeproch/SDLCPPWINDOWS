#include "render.h"
#include "map.h"
#include <iostream>
#include <chrono>

int toggleInterval = 500;
auto lastToggleTime = std::chrono::high_resolution_clock::now();

// State to track which key is pressed
enum class PlayerState {
    Idle,
    MovingW,
    MovingA,
    MovingS,
    MovingD
};

PlayerState playerState = PlayerState::Idle;
const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

void Keyboard::ReadKeyboardInput() {
    
    // Update player state based on key press
    if (keyboardState[SDL_SCANCODE_W]) {
        playerState = PlayerState::MovingW;
    } else if (keyboardState[SDL_SCANCODE_A]) {
        playerState = PlayerState::MovingA;
    } else if (keyboardState[SDL_SCANCODE_S]) {
        playerState = PlayerState::MovingS;
    } else if (keyboardState[SDL_SCANCODE_D]) {
        playerState = PlayerState::MovingD;
    } else {
        playerState = PlayerState::Idle;
    }
}

void Render::DeterminePlayerTexture() {
    // Calculate elapsed time for idle animation
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastToggleTime).count();

    if (playerState == PlayerState::Idle) {
        // Toggle between idle textures if no key is pressed
        if (elapsedTime >= toggleInterval) {
            showImage1 = !showImage1;
            lastToggleTime = currentTime; // reset the timer
        }

        // Render the appropriate idle texture
        if (showImage1) {
            SDL_RenderCopy(renderer, imageTexture1, NULL, &dstRect);
        } else {
            SDL_RenderCopy(renderer, imageTexture2, NULL, &dstRect);
        }
    } else {
        // Render specific textures based on the key pressed
        switch (playerState) {
            case PlayerState::MovingW:
        
                SDL_RenderCopy(renderer, imageTextureW, NULL, &dstRect);
                break;
            case PlayerState::MovingA:
                
                SDL_RenderCopy(renderer, imageTextureA, NULL, &dstRect);
                break;
            case PlayerState::MovingS:
                
                SDL_RenderCopy(renderer, imageTextureS, NULL, &dstRect);
                break;
            case PlayerState::MovingD:
                
                SDL_RenderCopy(renderer, imageTextureD, NULL, &dstRect);
                break;
            default:
                break;
        }
    }
}
