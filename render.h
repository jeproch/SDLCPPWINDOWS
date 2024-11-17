#ifndef RENDER_H
#define RENDER_H

#include "src/include/SDL.h"
#include <string>

extern  SDL_Window* window;
extern  SDL_Renderer* renderer;
extern bool isRunning;
extern SDL_Event event;

namespace Render {
    int InitializeSDL();
    void CleanUp();
    void RenderLoop();
    void SetBackgroundColour(int r, int g, int b, int a);
    void FreeTextures();
    void DeterminePlayerTexture();
}

#endif