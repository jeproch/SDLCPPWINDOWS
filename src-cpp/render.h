#ifndef RENDER_H
#define RENDER_H

#include "./SDL.h" 
#include "./SDL_image.h"
#include <string>

extern  SDL_Window* window;
extern  SDL_Renderer* renderer;
extern bool isRunning;
extern bool showImage1;

extern SDL_Texture* imageTexture1;
extern SDL_Texture* imageTexture2;
extern SDL_Texture* imageTextureA;
extern SDL_Texture* imageTextureD;
extern SDL_Texture* imageTextureS;
extern SDL_Texture* imageTextureW;


extern SDL_Rect dstRect;
extern SDL_Event event;

namespace Render {
    int InitializeSDL();
    void CleanUp();
    void RenderLoop();
    void SetBackgroundColour(int r, int g, int b, int a);
    void FreeTextures();
    void DeterminePlayerTexture();
}

namespace Keyboard {
    void ReadKeyboardInput();
}

#endif