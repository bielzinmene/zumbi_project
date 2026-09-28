#include "TitleState.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "StageState.h"
#include "Text.h"

namespace {
const char* kPrompt = "PRESSIONE ESPACO PARA JOGAR";
}

TitleState::TitleState()
    : m_prompt(nullptr), m_promptObject(nullptr), m_blinkTime(0.0f),
      m_promptVisible(true), m_assetsLoaded(false) {}

void TitleState::LoadAssets() {
    if (m_assetsLoaded) return;
    m_assetsLoaded = true;
    auto* background = new GameObject();
    background->renderLayer = -1;
    auto* image = new SpriteRenderer(*background, "resources/img/Title.png");
    image->SetCameraFollower(true);
    background->AddComponent(image);
    AddObject(background);

    m_promptObject = new GameObject();
    m_promptObject->renderLayer = 1;
    m_prompt = new Text(*m_promptObject, "resources/font/neodgm.ttf", 30,
                        Text::TextStyle::BLENDED, kPrompt, {255, 238, 184, 255});
    m_promptObject->box.x = (1200.0f - m_promptObject->box.w) * 0.5f;
    m_promptObject->box.y = 790.0f;
    m_promptObject->AddComponent(m_prompt);
    AddObject(m_promptObject);
}

void TitleState::Start() {
    if (started) return;
    Camera::Unfollow();
    Camera::pos = Vec2();
    LoadAssets();
    started = true;
    StartArray();
}

void TitleState::Pause() {}
void TitleState::Resume() {}

void TitleState::Update(float dt) {
    const auto& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }
    if (input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new StageState());
        return;
    }
    m_blinkTime += dt;
    if (m_blinkTime >= 0.6f) {
        m_blinkTime -= 0.6f;
        m_promptVisible = !m_promptVisible;
        m_prompt->SetText(m_promptVisible ? kPrompt : "");
        if (m_promptVisible) m_promptObject->box.x = (1200.0f - m_promptObject->box.w) * 0.5f;
    }
    UpdateArray(dt);
}

void TitleState::Render() { RenderArray(); }
