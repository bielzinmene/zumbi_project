#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>

class Sound {
public:
    Sound();
    explicit Sound(const std::string& file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    bool IsOpen() const;

private:
    Mix_Chunk* m_chunk;
    int m_channel;
};

#endif