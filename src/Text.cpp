#include "Text.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include <cmath>
#include <iostream>

Text::Text(GameObject& associated, const std::string& fontFile, int fontSize,
           TextStyle style, const std::string& text, SDL_Color color)
    : Component(associated), m_texture(nullptr), m_text(text), m_style(style),
      m_fontFile(fontFile), m_fontSize(fontSize), m_color(color) {
    RemakeTexture();
}

Text::~Text() { SDL_DestroyTexture(m_texture); }

void Text::Update(float) {}

void Text::Render() {
    if (!m_texture) return;
    SDL_Rect dst = {
        static_cast<int>(std::round(associated.box.x - Camera::pos.x)),
        static_cast<int>(std::round(associated.box.y - Camera::pos.y)),
        static_cast<int>(associated.box.w),
        static_cast<int>(associated.box.h)
    };
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_texture, nullptr,
                     &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Text::SetText(const std::string& text) {
    if (m_text == text) return;
    m_text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    m_color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    if (m_style == style) return;
    m_style = style;
    RemakeTexture();
}

void Text::SetFontFile(const std::string& file) {
    if (m_fontFile == file) return;
    m_fontFile = file;
    RemakeTexture();
}

void Text::SetFontSize(int size) {
    if (m_fontSize == size) return;
    m_fontSize = size;
    RemakeTexture();
}

void Text::RemakeTexture() {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    associated.box.w = 0.0f;
    associated.box.h = 0.0f;
    if (m_text.empty()) return;

    m_font = Resources::GetFont(m_fontFile, m_fontSize);
    if (!m_font) return;
    SDL_Surface* surface = nullptr;
    if (m_style == TextStyle::SOLID) {
        surface = TTF_RenderUTF8_Solid(m_font.get(), m_text.c_str(), m_color);
    } else if (m_style == TextStyle::SHADED) {
        const SDL_Color black = {0, 0, 0, 255};
        surface = TTF_RenderUTF8_Shaded(m_font.get(), m_text.c_str(), m_color, black);
    } else {
        surface = TTF_RenderUTF8_Blended(m_font.get(), m_text.c_str(), m_color);
    }
    if (!surface) {
        std::cerr << "[Text] renderizacao: " << TTF_GetError() << std::endl;
        return;
    }
    m_texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    if (m_texture) {
        associated.box.w = static_cast<float>(surface->w);
        associated.box.h = static_cast<float>(surface->h);
    } else {
        std::cerr << "[Text] textura: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
}
