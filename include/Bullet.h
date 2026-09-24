#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
    void Update(float dt) override;
    void Render() override;
    int GetDamage() const;
private:
    Vec2 m_velocity;
    float m_rangeLeft;
    int m_damage;
};
#endif
