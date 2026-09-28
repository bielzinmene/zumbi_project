#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::s_imageTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::s_fontTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::s_musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::s_soundTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file) {
    auto found = s_imageTable.find(file);
    if (found != s_imageTable.end()) return found->second;
    SDL_Texture* raw = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!raw) {
        std::cerr << "[Resources] imagem: " << file << " | " << IMG_GetError() << std::endl;
        return {};
    }
    auto image = std::shared_ptr<SDL_Texture>(raw, SDL_DestroyTexture);
    s_imageTable.emplace(file, image);
    return image;
}

void Resources::ClearImages() {
    for (auto it = s_imageTable.begin(); it != s_imageTable.end();) {
        if (it->second.unique()) it = s_imageTable.erase(it);
        else ++it;
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(const std::string& file, int size) {
    if (size <= 0) return {};
    const std::string key = file + "#" + std::to_string(size);
    auto found = s_fontTable.find(key);
    if (found != s_fontTable.end()) return found->second;
    TTF_Font* raw = TTF_OpenFont(file.c_str(), size);
    if (!raw) {
        std::cerr << "[Resources] fonte: " << file << " | " << TTF_GetError() << std::endl;
        return {};
    }
    auto font = std::shared_ptr<TTF_Font>(raw, TTF_CloseFont);
    s_fontTable.emplace(key, font);
    return font;
}

void Resources::ClearFonts() {
    for (auto it = s_fontTable.begin(); it != s_fontTable.end();) {
        if (it->second.unique()) it = s_fontTable.erase(it);
        else ++it;
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(const std::string& file) {
    auto found = s_musicTable.find(file);
    if (found != s_musicTable.end()) return found->second;
    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) {
        std::cerr << "[Resources] musica: " << file << " | " << Mix_GetError() << std::endl;
        return {};
    }
    auto stored = std::shared_ptr<Mix_Music>(music, Mix_FreeMusic);
    s_musicTable.emplace(file, stored);
    return stored;
}

void Resources::ClearMusics() {
    for (auto it = s_musicTable.begin(); it != s_musicTable.end();) {
        if (it->second.unique()) it = s_musicTable.erase(it);
        else ++it;
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file) {
    auto found = s_soundTable.find(file);
    if (found != s_soundTable.end()) return found->second;
    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if (!sound) {
        std::cerr << "[Resources] som: " << file << " | " << Mix_GetError() << std::endl;
        return {};
    }
    auto stored = std::shared_ptr<Mix_Chunk>(sound, Mix_FreeChunk);
    s_soundTable.emplace(file, stored);
    return stored;
}

void Resources::ClearSounds() {
    for (auto it = s_soundTable.begin(); it != s_soundTable.end();) {
        if (it->second.unique()) it = s_soundTable.erase(it);
        else ++it;
    }
}

void Resources::ClearAll() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    ClearImages();
    ClearFonts();
    ClearMusics();
    ClearSounds();
}
