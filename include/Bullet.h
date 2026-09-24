#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
           bool targetsPlayer);
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
    int GetDamage() const;
    bool TargetsPlayer() const;
private:
    Vec2 m_velocity;
    float m_rangeLeft;
    int m_damage;
    bool m_targetsPlayer;
};
#endif
