#include "Gun.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Bullet.h"
#include "Game.h"
#include <cmath>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated), m_owner(character), m_shotSound("resources/audio/Range.wav"),
      m_reloadSound("resources/audio/PumpAction.mp3"), m_phase(Phase::READY), m_angle(0.0f) {
    associated.AddComponent(new SpriteRenderer(associated, "resources/img/Gun.png", 3, 2));
    auto* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0.0f));
    animator->AddAnimation("reloading", Animation(1, 5, 0.06f));
    animator->AddAnimation("idle_left", Animation(0, 0, 0.0f, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloading_left", Animation(1, 5, 0.06f, SDL_FLIP_VERTICAL));
    associated.AddComponent(animator);
    SelectAnimation();
}

void Gun::Place(const GameObject& owner) {
    const Vec2 direction(std::cos(m_angle), std::sin(m_angle));
    const Vec2 center = owner.box.Center() + direction * 30.0f;
    associated.box.x = center.x - associated.box.w * 0.5f;
    associated.box.y = center.y - associated.box.h * 0.5f;
    associated.angleDeg = m_angle * 180.0 / std::acos(-1.0);
    // a arma compartilha a profundidade dos pes do personagem.
    associated.renderLayer = owner.renderLayer;
    associated.renderOffsetY = owner.GetRenderY() - (associated.box.y + associated.box.h);
}

void Gun::SelectAnimation() {
    std::string animation = m_phase == Phase::RELOADING ? "reloading" : "idle";
    if (std::cos(m_angle) < 0.0f) animation += "_left";
    associated.GetComponent<Animator>()->SetAnimation(animation);
}

void Gun::Start() {
    if (auto owner = m_owner.lock()) Place(*owner);
}

void Gun::Update(float dt) {
    auto owner = m_owner.lock();
    if (!owner || owner->IsDead()) {
        associated.RequestDelete();
        return;
    }
    Place(*owner);
    if (m_phase == Phase::READY) return;

    // preserva o tempo restante ao atravessar uma transicao.
    float remaining = dt;
    while (m_phase != Phase::READY) {
        const float duration = m_phase == Phase::RELOADING ? 0.3f : 0.1f;
        const float untilNext = duration - m_phaseTimer.Get();
        if (remaining < untilNext) {
            m_phaseTimer.Update(remaining);
            break;
        }
        remaining -= untilNext;
        m_phaseTimer.Restart();
        switch (m_phase) {
        case Phase::RECOIL:
            m_phase = Phase::RELOADING;
            m_reloadSound.Play();
            break;
        case Phase::RELOADING: m_phase = Phase::SETTLING; break;
        case Phase::SETTLING: m_phase = Phase::READY; break;
        case Phase::READY: break;
        }
        SelectAnimation();
    }
}

void Gun::Shoot(Vec2 target) {
    auto owner = m_owner.lock();
    if (!owner || owner->IsDead() || m_phase != Phase::READY) return;
    const Vec2 aim = target - owner->box.Center();
    if (aim.Magnitude() == 0.0f) return;
    m_angle = aim.InclinationX();
    Place(*owner);
    const Vec2 direction = aim.Normalized();
    const Vec2 muzzle = associated.box.Center() + direction * (associated.box.w * 0.5f);
    auto* projectile = new GameObject();
    projectile->AddComponent(new Bullet(*projectile, m_angle, 500.0f, 10, 800.0f));
    projectile->box.x = muzzle.x - projectile->box.w * 0.5f;
    projectile->box.y = muzzle.y - projectile->box.h * 0.5f;
    Game::GetInstance().GetState().AddObject(projectile);
    m_shotSound.Play();
    m_phase = Phase::RECOIL;
    m_phaseTimer.Restart();
    SelectAnimation();
}
void Gun::Render() {}
