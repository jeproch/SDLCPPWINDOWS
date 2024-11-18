#include "movement.h"
#include "render.h"
#include "map.h"
#include <iostream>
#include <chrono>

void Movement::PlayerMove() {
    static auto lastUpdate = std::chrono::steady_clock::now(); // Track the last update time
    const auto updateInterval = std::chrono::milliseconds(500); // Set the movement interval

    auto now = std::chrono::steady_clock::now();
    if (now - lastUpdate >= updateInterval) {
        // Enough time has passed, update movement
        switch (playerState)
        {
            case PlayerState::MovingW:
                dstRect.y += TILE_SIZE; 
                break;
            case PlayerState::MovingA:
                dstRect.x -= TILE_SIZE;
                break;
            case PlayerState::MovingS:
                dstRect.y -= TILE_SIZE;
                break;
            case PlayerState::MovingD:
                dstRect.x += TILE_SIZE;
                break;
            default:
                break;
        }

        lastUpdate = now; // Reset the timer
    }

    // Add rendering or input handling logic here without blocking
    std::cout << "Player at position: (" << dstRect.x << ", " << dstRect.y << ")" << std::endl;
}
