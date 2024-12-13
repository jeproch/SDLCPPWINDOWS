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
        // Collision detection
        switch (playerState) {
            case PlayerState::MovingW:
                // Check if the player can move upward
                if (map[(dstRect.y / TILE_SIZE) - 1][dstRect.x / TILE_SIZE] != 1) {
                    dstRect.y -= TILE_SIZE;
                }
                break;

            case PlayerState::MovingA:
                // Check if the player can move left
                if (map[(dstRect.y / TILE_SIZE)][(dstRect.x / TILE_SIZE) - 1] != 1) {
                    dstRect.x -= TILE_SIZE;
                }
                break;

            case PlayerState::MovingS:
                // Check if the player can move downward (boundary check for the last row)
                if ((dstRect.y / TILE_SIZE) + 1 < MAP_HEIGHT &&
                    map[(dstRect.y / TILE_SIZE) + 1][dstRect.x / TILE_SIZE] != 1) {
                    dstRect.y += TILE_SIZE;
                }
                break;

            case PlayerState::MovingD:
                // Check if the player can move right (boundary check for the last column)
                if ((dstRect.x / TILE_SIZE) + 1 < MAP_WIDTH &&
                    map[(dstRect.y / TILE_SIZE)][(dstRect.x / TILE_SIZE) + 1] != 1) {
                    dstRect.x += TILE_SIZE;
                }
                break;

            default:
                break;
        }

        lastUpdate = now; // Reset the timer
    }
}
