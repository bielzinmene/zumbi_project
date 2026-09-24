#include "Character.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Game.h"
#include "Gun.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Collider.h"
#include "Camera.h"
#include "AIController.h"
#include <vector>

Character* Character::player = nullptr;

Character::Character(GameObject& associated, const std::string& sprite)
    : Component(associated), m_moveSpeed(200.0f), m_health(100), m_facingLeft(false),
      m_hitSound("resources/audio/Hit1.wav"), m_deathSound("resources/audio/Dead.wav") {
    m_damageCooldown.Update(1.0f);
    associated.AddComponent(new SpriteRenderer(associated, sprite, 3, 4));
    auto* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(6, 9, 0.2f));
    animator->AddAnimation("walking", Animation(0, 5, 0.1f));
    animator->AddAnimation("dead", Animation(10, 11, 0.3f, SDL_FLIP_NONE, false));
    animator->AddAnimation("idle_left", Animation(6, 9, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("walking_left", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead_left", Animation(10, 11, 0.3f, SDL_FLIP_HORIZONTAL, false));
    associated.AddComponent(animator);
    animator->SetAnimation("idle");
}

Character::~Character() {
    if (player == this) player = nullptr;
    if (auto weapon = m_weapon.lock()) weapon->RequestDelete();
}

void Character::Start() {
    if (!associated.GetComponent<Collider>()) {
        associated.AddComponent(new Collider(associated, Vec2(0.58f, 0.72f), Vec2(0.0f, 9.0f)));
    }
    if (!m_weapon.expired()) return;
    State& state = Game::GetInstance().GetState();
    const auto owner = state.GetObjectPtr(&associated);
    if (owner.expired()) return;
    auto* weapon = new GameObject();
    weapon->AddComponent(new Gun(*weapon, owner));
    m_weapon = state.AddObject(weapon);
}

void Character::Update(float dt) {
    auto* animator = associated.GetComponent<Animator>();
    if (m_health <= 0) {
        animator->SetAnimation(m_facingLeft ? "dead_left" : "dead");
        m_deathTimer.Update(dt);
        if (m_deathTimer.Get() >= 2.0f) associated.RequestDelete();
        return;
    }

    m_damageCooldown.Update(dt);

    m_velocity = Vec2();
    std::vector<Vec2> shots;
    while (!m_commands.empty()) {
        const Command command = m_commands.front();
        m_commands.pop();
        if (command.type == CommandType::MOVE) {
            m_velocity = command.pos.Normalized() * m_moveSpeed;
        } else {
            shots.push_back(command.pos);
        }
    }
    associated.box.x += m_velocity.x * dt;
    associated.box.y += m_velocity.y * dt;
    // o disparo usa a posicao atualizada do corpo.
    if (auto weapon = m_weapon.lock()) {
        if (auto* gun = weapon->GetComponent<Gun>()) {
            for (const Vec2& target : shots) gun->Shoot(target);
        }
    }
    if (m_velocity.x != 0.0f) m_facingLeft = m_velocity.x < 0.0f;
    const bool moving = m_velocity.Magnitude() > 0.0f;
    const std::string animation = moving ? "walking" : "idle";
    animator->SetAnimation(animation + (m_facingLeft ? "_left" : ""));
}

void Character::Issue(Command task) {
    if (m_health > 0) m_commands.push(task);
}
void Character::Render() {}

bool Character::IsAlive() const { return m_health > 0; }
const GameObject& Character::GetObject() const { return associated; }

void Character::TakeDamage(int amount) {
    if (m_health <= 0 || m_damageCooldown.Get() < 1.0f || amount <= 0) return;
    m_health -= amount;
    m_damageCooldown.Restart();
    m_hitSound.Play();
    if (m_health <= 0) {
        m_health = 0;
        m_deathTimer.Restart();
        m_deathSound.Play();
        if (auto weapon = m_weapon.lock()) weapon->RequestDelete();
        if (auto* animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation(m_facingLeft ? "dead_left" : "dead");
        }
        if (auto* collider = associated.GetComponent<Collider>()) associated.RemoveComponent(collider);
        if (auto* ai = associated.GetComponent<AIController>()) ai->OnDeath();
        if (player == this) Camera::Unfollow();
    }
}

void Character::NotifyCollision(GameObject& other) {
    if (auto* bullet = other.GetComponent<Bullet>()) {
        if (bullet->TargetsPlayer() == (player == this)) TakeDamage(bullet->GetDamage());
    } else if (other.GetComponent<Zombie>()) {
        TakeDamage(10);
    }
}
