#include "PlayerController.h"
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}
void PlayerController::Start() {}
void PlayerController::Render() {}

void PlayerController::Update(float dt) {
    auto* character = associated.GetComponent<Character>();
    if (!character) return;
    const auto& input = InputManager::GetInstance();
    const float x = input.IsKeyDown(SDLK_d) - input.IsKeyDown(SDLK_a);
    const float y = input.IsKeyDown(SDLK_s) - input.IsKeyDown(SDLK_w);
    character->Issue(Character::Command(Character::CommandType::MOVE, x, y));
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        const Vec2 target = Vec2(input.GetMouseX(), input.GetMouseY()) + Camera::pos;
        character->Issue(Character::Command(Character::CommandType::SHOOT, target.x, target.y));
    }
}
