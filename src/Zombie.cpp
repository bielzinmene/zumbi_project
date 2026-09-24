#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "GameObject.h"
#include "Character.h"
#include "Bullet.h"
#include "Collider.h"

int Zombie::s_aliveCount = 0;

Zombie::Zombie(GameObject& associated)
    : Component(associated), m_hitpoints(100),
      m_deathSound("resources/audio/Dead.wav"),
      m_hitSound("resources/audio/Hit0.wav"), m_hit(false), m_facingLeft(false) {
    ++s_aliveCount;
    auto* renderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);
    auto* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.2f));
    animator->AddAnimation("walking_left", Animation(0, 3, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("hit", Animation(4, 4, 0.0f));
    animator->AddAnimation("hit_left", Animation(4, 4, 0.0f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->AddAnimation("dead_left", Animation(5, 5, 0.0f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(animator);
    animator->SetAnimation("walking");
}

Zombie::~Zombie() {
    if (m_hitpoints > 0) --s_aliveCount;
}

void Zombie::Start() {
    if (!associated.GetComponent<Collider>()) {
        associated.AddComponent(new Collider(associated, Vec2(0.62f, 0.7f), Vec2(0.0f, 8.0f)));
    }
}

int Zombie::AliveCount() { return s_aliveCount; }

void Zombie::Damage(int damage) {
    if (m_hitpoints <= 0 || damage <= 0) return;
    m_hitpoints -= damage;
    m_hitSound.Play();
    auto* animator = associated.GetComponent<Animator>();
    if (m_hitpoints <= 0) {
        --s_aliveCount;
        m_hit = false;
        m_deathTimer.Restart();
        m_deathSound.Play();
        if (animator) animator->SetAnimation(m_facingLeft ? "dead_left" : "dead");
        if (auto* collider = associated.GetComponent<Collider>()) associated.RemoveComponent(collider);
    } else {
        m_hit = true;
        m_hitTimer.Restart();
        if (animator) animator->SetAnimation(m_facingLeft ? "hit_left" : "hit");
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
            if (animator) animator->SetAnimation(m_facingLeft ? "walking_left" : "walking");
        }
    }
    if (Character::player && Character::player->IsAlive()) {
        const Vec2 towardPlayer = Character::player->GetObject().box.Center() - associated.box.Center();
        const Vec2 movement = towardPlayer.Normalized() * (55.0f * dt);
        associated.box.x += movement.x;
        associated.box.y += movement.y;
        if (movement.x != 0.0f) m_facingLeft = movement.x < 0.0f;
        if (!m_hit) {
            if (auto* animator = associated.GetComponent<Animator>()) {
                animator->SetAnimation(m_facingLeft ? "walking_left" : "walking");
            }
        }
    }
}

void Zombie::Render() {}

void Zombie::NotifyCollision(GameObject& other) {
    auto* bullet = other.GetComponent<Bullet>();
    if (bullet && !bullet->TargetsPlayer()) Damage(bullet->GetDamage());
}
