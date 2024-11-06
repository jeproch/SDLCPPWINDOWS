#include <iostream>
#include "render.h"

int main(int argc, char* argv[]) {
    if (Render::InitializeSDL() != 0) return 1;

    Render::RenderLoop();

    Render::CleanUp();
    return 0;
}
