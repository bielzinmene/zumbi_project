#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(GameObject& associated)
    : Component(associated), m_frameStart(0), m_frameEnd(0),
      m_frameTime(0), m_currentFrame(0), m_timeElapsed(0) {}

void Animator::Update(float dt) {
    if (m_frameTime == 0.0f) return;

    // Usando 1.0f temporariamente por frame como sugerido ate calcularmos o dt real no futuro
    m_timeElapsed += 1.0f;

    if (m_timeElapsed > m_frameTime) {
        m_currentFrame++;
        m_timeElapsed -= m_frameTime;

        if (m_currentFrame > m_frameEnd) {
            m_currentFrame = m_frameStart;
        }

        SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>();
        if (renderer != nullptr) {
            renderer->SetFrame(m_currentFrame);
        }
    }
}

void Animator::Render() { /* Vazio */ }

void Animator::AddAnimation(const std::string& name, const Animation& anim) {
    if (m_animations.find(name) == m_animations.end()) {
        m_animations.emplace(name, anim);
    }
}

void Animator::SetAnimation(const std::string& name) {
    auto it = m_animations.find(name);
    if (it != m_animations.end()) {
        m_frameStart = it->second.frameStart;
        m_frameEnd = it->second.frameEnd;
        m_frameTime = it->second.frameTime;

        m_currentFrame = m_frameStart;
        m_timeElapsed = 0;

        SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>();
        if (renderer != nullptr) {
            renderer->SetFrame(m_currentFrame);
        }
    }
}