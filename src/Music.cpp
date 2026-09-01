#include "../include/Music.h"
#include <iostream>

Music::Music() : m_music(nullptr) {}

Music::Music(const std::string& file) : Music() {
    Open(file);
}

Music::~Music() {
    Stop(0);
    if (m_music != nullptr) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}

void Music::Open(const std::string& file) {
    if (m_music != nullptr) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }

    m_music = Mix_LoadMUS(file.c_str());
    if (m_music == nullptr) {
        std::cerr << "[Music] Falha ao carregar trilha sonora: " << file
                  << " | Erro Mix: " << Mix_GetError() << std::endl;
    }
}

void Music::Play(int times) {
    if (m_music != nullptr) {
        if (Mix_PlayMusic(m_music, times) != 0) {
            std::cerr << "[Music] Erro ao reproduzir musica: "
                      << Mix_GetError() << std::endl;
        }
    }
}

void Music::Stop(int msToStop) {
    if (msToStop > 0) {
        Mix_FadeOutMusic(msToStop);
    } else {
        Mix_HaltMusic();
    }
}

bool Music::IsOpen() const {
    return m_music != nullptr;
}