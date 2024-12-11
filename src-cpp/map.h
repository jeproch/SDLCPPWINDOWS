#ifndef MAP_H
#define MAP_H

#include "./SDL.h" 
#include "./SDL_image.h"
#include <string>

extern const int SCREEN_WIDTH; // 64 * 16
extern const int SCREEN_HEIGHT; // 64 * 9
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern const int TILE_SIZE; // Size of each tile in pixels
extern int map[18][32];

namespace Map {
    void DrawMap(SDL_Renderer* renderer);
}

#endif