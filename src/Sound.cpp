#include "Sound.h"
#include "Resources.h"
#include <iostream>

Sound::Sound() : m_chunk(nullptr), m_channel(-1) {}

Sound::Sound(const std::string& file) : Sound() {
    Open(file);
}

Sound::~Sound() {
    Stop();
    // A desalocacao da memoria e centralizada na classe Resources
}

void Sound::Open(const std::string& file) {
    m_chunk = Resources::GetSound(file);
}

void Sound::Play(int times) {
    if (m_chunk != nullptr) {
        // times = 1 toca uma vez; loops = 0 indica sem repeticoes extras
        int loops = times - 1;
        m_channel = Mix_PlayChannel(-1, m_chunk, loops);
        if (m_channel == -1) {
            std::cerr << "[Sound] Erro ao reproduzir canal de audio: " << Mix_GetError() << std::endl;
        }
    }
}

void Sound::Stop() {
    if (m_chunk != nullptr && m_channel != -1) {
        Mix_HaltChannel(m_channel);
        m_channel = -1;
    }
}

bool Sound::IsOpen() const {
    return m_chunk != nullptr;
}