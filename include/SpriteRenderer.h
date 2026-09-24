#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include <string>

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW = 1, int frameCountH = 1);

    void Open(const std::string& file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetScale(float scaleX, float scaleY);
    void SetCameraFollower(bool enabled);

    void Update(float dt) override;
    void Render() override;

private:
    Sprite m_sprite;
};

#endif