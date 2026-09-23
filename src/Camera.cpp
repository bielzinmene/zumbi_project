#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::s_focus = nullptr;

void Camera::Follow(GameObject* newFocus) { s_focus = newFocus; }
void Camera::Unfollow() { s_focus = nullptr; speed = Vec2(); }
GameObject* Camera::GetFocus() { return s_focus; }

void Camera::Update(float dt) {
    if (s_focus) {
        int width = 0, height = 0;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &width, &height);
        pos = s_focus->box.Center() - Vec2(width / 2.0f, height / 2.0f);
        speed = Vec2();
        return;
    }
    const auto& input = InputManager::GetInstance();
    const bool right = input.IsKeyDown(RIGHT_ARROW_KEY) || input.IsKeyDown(SDLK_d);
    const bool left = input.IsKeyDown(LEFT_ARROW_KEY) || input.IsKeyDown(SDLK_a);
    const bool down = input.IsKeyDown(DOWN_ARROW_KEY) || input.IsKeyDown(SDLK_s);
    const bool up = input.IsKeyDown(UP_ARROW_KEY) || input.IsKeyDown(SDLK_w);
    // normaliza para manter a mesma velocidade nas diagonais.
    const Vec2 direction(right - left, down - up);
    speed = direction.Normalized() * 300.0f;
    pos = pos + speed * dt;
}
