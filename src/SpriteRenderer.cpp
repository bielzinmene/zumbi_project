#include "SpriteRenderer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW, int frameCountH)
    : Component(associated), m_sprite(file, frameCountW, frameCountH) {

    associated.box.w = m_sprite.GetWidth();
    associated.box.h = m_sprite.GetHeight();
    m_sprite.SetFrame(0); // inicia no frame 0
}

void SpriteRenderer::Open(const std::string& file) {
    m_sprite.Open(file);
    associated.box.w = m_sprite.GetWidth();
    associated.box.h = m_sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    m_sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    m_sprite.SetFrame(frame);
    m_sprite.SetFlip(flip);
}

void SpriteRenderer::Update(float dt) { (void)dt; /* vazio por enquanto */ }

void SpriteRenderer::Render() {
    m_sprite.Render(associated.box.x, associated.box.y, 1.0f, associated.angleDeg);
}

void SpriteRenderer::SetCameraFollower(bool enabled) {
    m_sprite.cameraFollower = enabled;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    const Vec2 center = associated.box.Center();
    m_sprite.SetScale(scaleX, scaleY);
    associated.box.w = m_sprite.GetWidth();
    associated.box.h = m_sprite.GetHeight();
    associated.box.x = center.x - associated.box.w * 0.5f;
    associated.box.y = center.y - associated.box.h * 0.5f;
}
