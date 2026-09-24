#ifndef GUN_H
#define GUN_H
#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"
#include <memory>

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> character);
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void Shoot(Vec2 target);
private:
    enum class Phase { READY, RECOIL, RELOADING, SETTLING };
    std::weak_ptr<GameObject> m_owner;
    Sound m_shotSound;
    Sound m_reloadSound;
    Timer m_phaseTimer;
    Phase m_phase;
    float m_angle;
    void Place(const GameObject& owner);
    void SelectAnimation();
};
#endif
