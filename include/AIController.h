#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class AIController : public Component {
public:
    explicit AIController(GameObject& associated);
    ~AIController() override;
    void Update(float dt) override;
    void Render() override;
    static int AliveCount();
    void OnDeath();

private:
    enum class Mode { RESTING, MOVING };
    Mode m_mode;
    Timer m_restTimer;
    Vec2 m_destination;
    bool m_countedAlive;
    static int s_aliveCount;
};

#endif
