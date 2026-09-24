#include "WaveSpawner.h"
#include "AIController.h"
#include "Camera.h"
#include "Character.h"
#include "Game.h"
#include "GameObject.h"
#include "Zombie.h"
#include <cstdlib>

WaveSpawner::WaveSpawner(GameObject& associated)
    : Component(associated), m_waveIndex(0), m_waiting(false) {
    using Type = WaveAction::Type;
    m_waves.emplace_back(Wave{{Type::WAIT, 1.5f}, Type::ZOMBIE,
        {Type::WAIT, 1.2f}, Type::ZOMBIE, {Type::WAIT, 0.9f}, Type::ZOMBIE,
        {Type::WAIT, 0.7f}, Type::ZOMBIE, {Type::WAIT, 0.5f}, Type::NPC});
    m_waves.emplace_back(Wave{{Type::WAIT, 1.5f}, Type::ZOMBIE, Type::ZOMBIE,
        {Type::WAIT, 0.9f}, Type::ZOMBIE, {Type::WAIT, 0.7f}, Type::NPC,
        Type::ZOMBIE, Type::ZOMBIE, {Type::WAIT, 0.5f}, Type::ZOMBIE,
        Type::NPC});
    m_waves.emplace_back(Wave{{Type::WAIT, 1.2f}, Type::ZOMBIE, Type::ZOMBIE,
        {Type::WAIT, 0.8f}, Type::ZOMBIE, Type::NPC, Type::ZOMBIE,
        {Type::WAIT, 0.5f}, Type::ZOMBIE, Type::ZOMBIE, Type::NPC,
        {Type::WAIT, 0.35f}, Type::ZOMBIE, Type::ZOMBIE, Type::ZOMBIE});
    LoadWave();
}

void WaveSpawner::LoadWave() {
    while (!m_pending.empty()) m_pending.pop();
    m_waiting = false;
    m_waitTimer.Restart();
    if (m_waveIndex < m_waves.size()) {
        for (const WaveAction& action : m_waves[m_waveIndex].actions) m_pending.push(action);
    }
}

void WaveSpawner::Spawn(WaveAction::Type type) {
    int width = 0;
    int height = 0;
    SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &width, &height);
    const float horizontal = static_cast<float>(std::rand()) / RAND_MAX;
    const float vertical = static_cast<float>(std::rand()) / RAND_MAX;
    const int edge = std::rand() % 4;
    const float margin = 110.0f;
    Vec2 position = Camera::pos;
    if (edge == 0 || edge == 1) {
        position.x += horizontal * width;
        position.y += edge == 0 ? -margin : height + margin;
    } else {
        position.x += edge == 2 ? -margin : width + margin;
        position.y += vertical * height;
    }

    auto* enemy = new GameObject();
    enemy->box.x = position.x;
    enemy->box.y = position.y;
    if (type == WaveAction::Type::ZOMBIE) {
        enemy->AddComponent(new Zombie(*enemy));
    } else {
        enemy->AddComponent(new Character(*enemy, "resources/img/NPC.png"));
        enemy->AddComponent(new AIController(*enemy));
    }
    Game::GetInstance().GetState().AddObject(enemy);
}

void WaveSpawner::Update(float dt) {
    if (!Character::player || !Character::player->IsAlive()) return;
    if (m_waveIndex >= m_waves.size()) {
        associated.RequestDelete();
        return;
    }

    if (m_waiting) m_waitTimer.Update(dt);
    while (!m_pending.empty()) {
        const WaveAction action = m_pending.front();
        if (action.type == WaveAction::Type::WAIT) {
            if (!m_waiting) {
                m_waiting = true;
                m_waitTimer.Restart();
                return;
            }
            if (m_waitTimer.Get() < action.seconds) return;
            m_waiting = false;
            m_waitTimer.Restart();
        } else {
            Spawn(action.type);
        }
        m_pending.pop();
    }

    if (Zombie::AliveCount() == 0 && AIController::AliveCount() == 0) {
        ++m_waveIndex;
        if (m_waveIndex == m_waves.size()) associated.RequestDelete();
        else LoadWave();
    }
}

void WaveSpawner::Render() {}
