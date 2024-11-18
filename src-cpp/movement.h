#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include "./SDL.h" 
#include "./SDL_image.h"
#include <string>

namespace Movement {
    void PlayerMove();
}

extern const Uint8* keyboardState;

enum class PlayerState {
    Idle,
    MovingW,
    MovingA,
    MovingS,
    MovingD
};

extern PlayerState playerState;



#endif