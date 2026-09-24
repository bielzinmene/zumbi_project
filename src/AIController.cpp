#include "AIController.h"
#include "Character.h"
#include "GameObject.h"

int AIController::s_aliveCount = 0;

AIController::AIController(GameObject& associated)
    : Component(associated), m_mode(Mode::RESTING), m_countedAlive(true) {
    ++s_aliveCount;
}

AIController::~AIController() { OnDeath(); }

int AIController::AliveCount() { return s_aliveCount; }

void AIController::OnDeath() {
    if (m_countedAlive) {
        --s_aliveCount;
        m_countedAlive = false;
    }
}

void AIController::Update(float dt) {
    Character* player = Character::player;
    Character* self = associated.GetComponent<Character>();
    if (!player || !player->IsAlive() || !self || !self->IsAlive()) return;

    if (m_mode == Mode::RESTING) {
        m_restTimer.Update(dt);
        if (m_restTimer.Get() >= 1.8f) {
            m_destination = player->GetObject().box.Center();
            m_mode = Mode::MOVING;
        }
        return;
    }

    const Vec2 toward = m_destination - associated.box.Center();
    if (toward.Magnitude() <= 340.0f) {
        const Vec2 target = player->GetObject().box.Center();
        self->Issue(Character::Command(Character::CommandType::SHOOT, target.x, target.y));
        m_restTimer.Restart();
        m_mode = Mode::RESTING;
    } else {
        const Vec2 direction = toward.Normalized();
        self->Issue(Character::Command(Character::CommandType::MOVE,
            direction.x * 0.55f, direction.y * 0.55f));
    }
}

void AIController::Render() {}
