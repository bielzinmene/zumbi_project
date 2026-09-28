#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Music.h"
#include "State.h"

class StageState : public State {
public:
    StageState();
    ~StageState() override;

    void LoadAssets() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Update(float dt) override;
    void Render() override;

private:
    Music m_music;
    std::weak_ptr<GameObject> m_player;
    std::weak_ptr<GameObject> m_spawner;
    bool m_assetsLoaded;
    void CheckCollisions();
    void RemoveDeadObjects();
};

#endif
