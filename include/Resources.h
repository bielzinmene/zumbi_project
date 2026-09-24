#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <memory>
#include <string>
#include <unordered_map>

class Resources {
public:
    static std::shared_ptr<SDL_Texture> GetImage(const std::string& file);
    static void ClearImages();
    static std::shared_ptr<TTF_Font> GetFont(const std::string& file, int size);
    static void ClearFonts();

    static std::shared_ptr<Mix_Music> GetMusic(const std::string& file);
    static void ClearMusics();
    static std::shared_ptr<Mix_Chunk> GetSound(const std::string& file);
    static void ClearSounds();
    static void ClearAll();

private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> s_imageTable;
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> s_fontTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> s_musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> s_soundTable;
};

#endif
