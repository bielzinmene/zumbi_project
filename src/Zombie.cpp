#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), m_hitpoints(100),
      m_deathSound("resources/audio/Dead.wav"),
      m_hitSound("resources/audio/Hit0.wav"), m_hit(false) {
    auto* renderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);
    auto* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.2f));
    animator->AddAnimation("hit", Animation(4, 4, 0.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    associated.AddComponent(animator);
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    if (m_hitpoints <= 0 || damage <= 0) return;
    m_hitpoints -= damage;
    m_hitSound.Play();
    auto* animator = associated.GetComponent<Animator>();
    if (m_hitpoints <= 0) {
        m_hit = false;
        m_deathTimer.Restart();
        m_deathSound.Play();
        if (animator) animator->SetAnimation("dead");
    } else {
        m_hit = true;
        m_hitTimer.Restart();
        if (animator) animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {
    if (m_hitpoints <= 0) {
        m_deathTimer.Update(dt);
        if (m_deathTimer.Get() >= 5.0f) associated.RequestDelete();
        return;
    }
    if (m_hit) {
        m_hitTimer.Update(dt);
        if (m_hitTimer.Get() >= 0.5f) {
            m_hit = false;
            auto* animator = associated.GetComponent<Animator>();
            if (animator) animator->SetAnimation("walking");
        }
    }
    const auto& input = InputManager::GetInstance();
    const Vec2 mouseWorld = Vec2(input.GetMouseX(), input.GetMouseY()) + Camera::pos;
    if (input.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains(mouseWorld)) {
        Damage(10);
    }
}

void Zombie::Render() {}
