#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;

private:
    int m_hitpoints;
    Sound m_deathSound;
    Sound m_hitSound;
    Timer m_hitTimer;
    Timer m_deathTimer;
    bool m_hit;
};

#endif