#ifndef WAVE_H
#define WAVE_H

#include <initializer_list>
#include <vector>

struct WaveAction {
    enum class Type { ZOMBIE, NPC, WAIT };
    Type type;
    float seconds;
    WaveAction(Type type, float seconds = 0.0f) : type(type), seconds(seconds) {}
};

struct Wave {
    std::vector<WaveAction> actions;
    Wave(std::initializer_list<WaveAction> actions) : actions(actions) {}
};

#endif
