#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Character.h"
#include "Zombie.h"
#include "Collider.h"
#include <algorithm>
#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
               bool targetsPlayer)
    : Component(associated), m_velocity(std::cos(angle) * speed, std::sin(angle) * speed),
      m_rangeLeft(maxDistance), m_damage(damage), m_targetsPlayer(targetsPlayer) {
    auto* sprite = new SpriteRenderer(associated, "resources/img/Bullet.png");
    associated.AddComponent(sprite);
    associated.angleDeg = angle * 180.0 / std::acos(-1.0) + 90.0;
}

void Bullet::Start() {
    if (!associated.GetComponent<Collider>()) {
        associated.AddComponent(new Collider(associated, Vec2(0.6f, 0.65f)));
    }
}

void Bullet::Update(float dt) {
    if (m_rangeLeft <= 0.0f) {
        associated.RequestDelete();
        return;
    }
    const float distance = std::min(m_rangeLeft, m_velocity.Magnitude() * dt);
    const Vec2 step = m_velocity.Normalized() * distance;
    associated.box.x += step.x;
    associated.box.y += step.y;
    m_rangeLeft -= distance;
    if (m_rangeLeft <= 0.0f) associated.RequestDelete();
}
int Bullet::GetDamage() const { return m_damage; }
bool Bullet::TargetsPlayer() const { return m_targetsPlayer; }
void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject& other) {
    if (auto* character = other.GetComponent<Character>()) {
        if ((character == Character::player) == m_targetsPlayer) {
            associated.RequestDelete();
        }
    } else if (!m_targetsPlayer && other.GetComponent<Zombie>()) {
        associated.RequestDelete();
    }
}
