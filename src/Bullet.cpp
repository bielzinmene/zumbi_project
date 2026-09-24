#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <algorithm>
#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), m_velocity(std::cos(angle) * speed, std::sin(angle) * speed),
      m_rangeLeft(maxDistance), m_damage(damage) {
    auto* sprite = new SpriteRenderer(associated, "resources/img/Bullet.png");
    associated.AddComponent(sprite);
    sprite->SetScale(0.5f, 0.5f);
    associated.angleDeg = angle * 180.0 / std::acos(-1.0) + 90.0;
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
void Bullet::Render() {}
