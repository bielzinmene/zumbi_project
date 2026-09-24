#include "Sprite.h"
#include "Game.h"
#include <iostream>
#include "Resources.h"
#include "Camera.h"
#include <cmath>

Sprite::Sprite()
    : cameraFollower(false), m_texture(nullptr), m_width(0), m_height(0), m_clipRect{0, 0, 0, 0}, m_frameCountW(1), m_frameCountH(1), m_scale(1.0f, 1.0f), m_flip(SDL_FLIP_NONE) {}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH)
    : Sprite() {
    m_frameCountW = frameCountW > 0 ? frameCountW : 1;
    m_frameCountH = frameCountH > 0 ? frameCountH : 1;
    Open(file);
}

Sprite::~Sprite() {
    m_texture = nullptr;
}


void Sprite::Open(const std::string& file) {
    m_texture = Resources::GetImage(file);

    if (m_texture == nullptr) {
        return;
    }

    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height) != 0) {
        std::cerr << "[Sprite] Falha ao consultar dimensoes: " << SDL_GetError() << std::endl;
        return;
    }

    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    m_clipRect.x = x;
    m_clipRect.y = y;
    m_clipRect.w = w;
    m_clipRect.h = h;
}

void Sprite::Render(float x, float y, float parallax, double angle) {
    if (m_texture == nullptr) {
        return;
    }

    SDL_Rect dstRect;
    const float factor = cameraFollower ? 0.0f : parallax;
    dstRect.x = static_cast<int>(std::round(x - Camera::pos.x * factor));
    dstRect.y = static_cast<int>(std::round(y - Camera::pos.y * factor));
    dstRect.w = static_cast<int>(std::round(m_clipRect.w * m_scale.x));
    dstRect.h = static_cast<int>(std::round(m_clipRect.h * m_scale.y));

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_RenderCopyEx(renderer, m_texture, &m_clipRect, &dstRect, angle, nullptr, m_flip);
}

int Sprite::GetWidth() const {
    return static_cast<int>(std::round((m_width / m_frameCountW) * m_scale.x));
}

int Sprite::GetHeight() const {
    return static_cast<int>(std::round((m_height / m_frameCountH) * m_scale.y));
}

bool Sprite::IsOpen() const {
    return m_texture != nullptr;
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    m_frameCountW = frameCountW > 0 ? frameCountW : 1;
    m_frameCountH = frameCountH > 0 ? frameCountH : 1;
}

void Sprite::SetFrame(int frame) {
    if (frame < 0 || frame >= m_frameCountW * m_frameCountH) return;
    const int frameW = m_width / m_frameCountW;
    const int frameH = m_height / m_frameCountH;

    int currentX = (frame % m_frameCountW) * frameW;
    int currentY = (frame / m_frameCountW) * frameH;

    SetClip(currentX, currentY, frameW, frameH);
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX > 0.0f) m_scale.x = scaleX;
    if (scaleY > 0.0f) m_scale.y = scaleY;
}
Vec2 Sprite::GetScale() const { return m_scale; }
void Sprite::SetFlip(SDL_RendererFlip flip) { m_flip = flip; }
