#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <memory>
#include <string>

class Music {
public:
    Music();
    explicit Music(const std::string& file);

    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(const std::string& file);
    bool IsOpen() const;

private:
    std::shared_ptr<Mix_Music> m_music;
};

#endif
