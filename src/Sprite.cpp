#include "../include/Sprite.h"
#include "../include/Game.h"
#include <iostream>

Sprite::Sprite()
    : m_texture(nullptr), m_width(0), m_height(0), m_clipRect{0, 0, 0, 0} {}

Sprite::Sprite(const std::string& file) : Sprite() {
    Open(file);
} //construtir

Sprite::~Sprite() {
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
} //destruidor

void Sprite::Open(const std::string& file) {
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    } //carega imagem da textura

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    m_texture = IMG_LoadTexture(renderer, file.c_str());

    if (m_texture == nullptr) {
        std::cerr << "[Sprite] Falha ao carregar textura: " << file
                  << " | Erro SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height) != 0) {
        std::cerr << "[Sprite] Falha ao consultar dimensoes da textura: "
                  << SDL_GetError() << std::endl;
        return;
    }

    SetClip(0, 0, m_width, m_height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    m_clipRect.x = x;
    m_clipRect.y = y;
    m_clipRect.w = w;
    m_clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if (m_texture == nullptr) {
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = m_clipRect.w;
    dstRect.h = m_clipRect.h;

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_RenderCopy(renderer, m_texture, &m_clipRect, &dstRect);
}

int Sprite::GetWidth() const {
    return m_width;
}

int Sprite::GetHeight() const {
    return m_height;
}

bool Sprite::IsOpen() const {
    return m_texture != nullptr;
}