#include "Collider.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include <cmath>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), m_scale(scale), m_offset(offset) {}

void Collider::Start() { Update(0.0f); }

void Collider::Update(float) {
    box.w = associated.box.w * m_scale.x;
    box.h = associated.box.h * m_scale.y;
    Vec2 shifted = m_offset;
    shifted.Rotate(static_cast<float>(associated.angleDeg * std::acos(-1.0) / 180.0));
    const Vec2 center = associated.box.Center() + shifted;
    box.x = center.x - box.w * 0.5f;
    box.y = center.y - box.h * 0.5f;
}

void Collider::Render() {
#ifdef DEBUG
    const Vec2 center = box.Center();
    const float angle = static_cast<float>(associated.angleDeg * std::acos(-1.0) / 180.0);
    Vec2 corners[5] = {Vec2(box.x, box.y), Vec2(box.x + box.w, box.y),
                       Vec2(box.x + box.w, box.y + box.h), Vec2(box.x, box.y + box.h)};
    SDL_Point screen[5];
    for (int i = 0; i < 4; ++i) {
        Vec2 rotated = corners[i] - center;
        rotated.Rotate(angle);
        rotated = rotated + center - Camera::pos;
        screen[i] = {static_cast<int>(std::round(rotated.x)), static_cast<int>(std::round(rotated.y))};
    }
    screen[4] = screen[0];
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 40, 40, 255);
    SDL_RenderDrawLines(renderer, screen, 5);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
#endif
}

void Collider::SetScale(Vec2 scale) { m_scale = scale; Update(0.0f); }
void Collider::SetOffset(Vec2 offset) { m_offset = offset; Update(0.0f); }
