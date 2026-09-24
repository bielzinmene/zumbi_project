#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(GameObject& associated)
    : Component(associated), m_frameStart(0), m_frameEnd(0),
      m_frameTime(0), m_currentFrame(0), m_timeElapsed(0), m_flip(SDL_FLIP_NONE) {}

void Animator::Update(float dt) {
    if (m_frameTime <= 0.0f) return;

    m_timeElapsed += dt;

    // recupera todos os frames transcorridos mesmo quando um frame demora mais.
    while (m_timeElapsed >= m_frameTime) {
        m_currentFrame++;
        m_timeElapsed -= m_frameTime;

        if (m_currentFrame > m_frameEnd) {
            m_currentFrame = m_frameStart;
        }

        SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>();
        if (renderer != nullptr) {
            renderer->SetFrame(m_currentFrame, m_flip);
        }
    }
}

void Animator::Render() {}

void Animator::AddAnimation(const std::string& name, const Animation& anim) {
    if (m_animations.find(name) == m_animations.end()) {
        m_animations.emplace(name, anim);
    }
}

void Animator::SetAnimation(const std::string& name) {
    auto it = m_animations.find(name);
    if (it != m_animations.end() && name != m_current) {
        m_current = name;
        m_flip = it->second.flip;
        m_frameStart = it->second.frameStart;
        m_frameEnd = it->second.frameEnd;
        m_frameTime = it->second.frameTime;

        m_currentFrame = m_frameStart;
        m_timeElapsed = 0;

        SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>();
        if (renderer != nullptr) {
            renderer->SetFrame(m_currentFrame, m_flip);
        }
    }
}