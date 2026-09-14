#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;

    Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0.0f)
        : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {}
};

#endif