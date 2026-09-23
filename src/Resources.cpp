#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::s_imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::s_musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::s_soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    auto it = s_imageTable.find(file);
    if (it != s_imageTable.end()) {
        return it->second;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) {
        std::cerr << "[Resources] Erro ao carregar imagem: " << file
                  << " | SDL_GetError: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    s_imageTable[file] = texture;
    return texture;
}

void Resources::ClearImages() {
    for (auto& pair : s_imageTable) {
        if (pair.second != nullptr) {
            SDL_DestroyTexture(pair.second);
        }
    }
    s_imageTable.clear();
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    auto it = s_musicTable.find(file);
    if (it != s_musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "[Resources] Erro ao carregar musica: " << file
                  << " | Mix_GetError: " << Mix_GetError() << std::endl;
        return nullptr;
    }

    s_musicTable[file] = music;
    return music;
}

void Resources::ClearMusics() {
    for (auto& pair : s_musicTable) {
        if (pair.second != nullptr) {
            Mix_FreeMusic(pair.second);
        }
    }
    s_musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    auto it = s_soundTable.find(file);
    if (it != s_soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        std::cerr << "[Resources] Erro ao carregar som: " << file
                  << " | Mix_GetError: " << Mix_GetError() << std::endl;
        return nullptr;
    }

    s_soundTable[file] = chunk;
    return chunk;
}

void Resources::ClearSounds() {
    for (auto& pair : s_soundTable) {
        if (pair.second != nullptr) {
            Mix_FreeChunk(pair.second);
        }
    }
    s_soundTable.clear();
}

void Resources::ClearAll() {
    ClearImages();
    ClearMusics();
    ClearSounds();
}