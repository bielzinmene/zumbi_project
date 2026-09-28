#include "../include/Music.h"
#include <iostream>
#include "Resources.h"

Music::Music() : m_music(nullptr) {}

Music::Music(const std::string& file) : Music() {
    Open(file);
}

Music::~Music() {
    Stop(0);
    m_music.reset();
}

void Music::Open(const std::string& file) {
    m_music = Resources::GetMusic(file);
}

void Music::Play(int times) {
    if (m_music != nullptr) {
        if (Mix_PlayMusic(m_music.get(), times) != 0) {
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
