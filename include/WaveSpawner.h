#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include "Component.h"
#include "Timer.h"
#include "Wave.h"
#include <cstddef>
#include <queue>
#include <vector>

class WaveSpawner : public Component {
public:
    explicit WaveSpawner(GameObject& associated);
    void Update(float dt) override;
    void Render() override;

private:
    std::vector<Wave> m_waves;
    std::queue<WaveAction> m_pending;
    Timer m_waitTimer;
    std::size_t m_waveIndex;
    bool m_waiting;

    void LoadWave();
    void Spawn(WaveAction::Type type);
};

#endif
