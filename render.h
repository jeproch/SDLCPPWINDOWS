#ifndef RENDER_H
#define RENDER_H

#include "src/include/SDL.h"
#include <string>

extern  SDL_Window* window;
extern  SDL_Renderer* renderer;

namespace Render {
    int InitializeSDL();
    void CleanUp();
}

#endif