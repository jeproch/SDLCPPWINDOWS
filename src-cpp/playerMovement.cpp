#include "movement.h"
#include "render.h"
#include "map.h"
#include <iostream>
#include <chrono>

void Movement::PlayerMove() {
    static auto lastUpdate = std::chrono::steady_clock::now(); // Track the last update time
    const auto updateInterval = std::chrono::milliseconds(400); // Set the movement interval

    auto now = std::chrono::steady_clock::now();
    if (now - lastUpdate >= updateInterval) {
        // Enough time has passed, update movement
        //collision detection
        switch (playerState)
        {
            case PlayerState::MovingW:

                if (map[(dstRect.y / TILE_SIZE) - 1][dstRect.x / TILE_SIZE] != 1) {
                    dstRect.y -= TILE_SIZE;
                }
                         
                break;
            case PlayerState::MovingA:

                if (map[(dstRect.y / TILE_SIZE)][(dstRect.x / TILE_SIZE) - 1] != 1) {
                    dstRect.x -= TILE_SIZE;
                }
                
            
            
                break;
            case PlayerState::MovingS:


                if (map[(dstRect.y / TILE_SIZE) + 1][dstRect.x / TILE_SIZE] != 1) {
                    dstRect.y += TILE_SIZE;
                }
            
            
                break;
            case PlayerState::MovingD:
                
                
                if (map[(dstRect.y / TILE_SIZE)][(dstRect.x / TILE_SIZE) + 1] != 1) {
                    dstRect.x += TILE_SIZE;
                }
                
                
                break;
            default:
                break;
        }

        lastUpdate = now; // Reset the timer
    }

}
