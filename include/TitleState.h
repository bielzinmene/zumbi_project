#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
class Text;

class TitleState : public State {
public:
    TitleState();
    void LoadAssets() override;
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Update(float dt) override;
    void Render() override;

private:
    Text* m_prompt;
    GameObject* m_promptObject;
    float m_blinkTime;
    bool m_promptVisible;
    bool m_assetsLoaded;
};

#endif
