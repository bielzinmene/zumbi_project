#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "GameData.h"
#include "Music.h"
#include "State.h"

class EndState : public State {
public:
    explicit EndState(bool victory);
    ~EndState() override;
    void LoadAssets() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Update(float dt) override;
    void Render() override;

private:
    GameData m_result;
    Music m_music;
    bool m_assetsLoaded;
};

#endif
