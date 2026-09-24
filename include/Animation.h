#ifndef ANIMATION_H
#define ANIMATION_H

#define INCLUDE_SDL
#include "SDL_include.h"

class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;
    bool loop;

    Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0.0f,
              SDL_RendererFlip flip = SDL_FLIP_NONE, bool loop = true)
        : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(flip), loop(loop) {}
};

#endif
