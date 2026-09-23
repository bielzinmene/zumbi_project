#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <unordered_map>

class Resources {
public:
    static SDL_Texture* GetImage(const std::string& file);
    static void ClearImages();

    static Mix_Music* GetMusic(const std::string& file);
    static void ClearMusics();

    static Mix_Chunk* GetSound(const std::string& file);
    static void ClearSounds();

    static void ClearAll();

private:
    static std::unordered_map<std::string, SDL_Texture*> s_imageTable;
    static std::unordered_map<std::string, Mix_Music*> s_musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> s_soundTable;
};

#endif