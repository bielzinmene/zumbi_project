#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "Animation.h"
#include <unordered_map>
#include <string>

class Animator : public Component {
public:
    Animator(GameObject& associated);

    void Update(float dt) override;
    void Render() override;

    void SetAnimation(const std::string& name);
    void AddAnimation(const std::string& name, const Animation& anim);

private:
    std::unordered_map<std::string, Animation> m_animations;
    int m_frameStart;
    int m_frameEnd;
    float m_frameTime;
    int m_currentFrame;
    float m_timeElapsed;
    std::string m_current;
    SDL_RendererFlip m_flip;
};

#endif