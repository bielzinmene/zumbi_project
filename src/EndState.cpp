#include "EndState.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "Text.h"
#include "TitleState.h"

EndState::EndState(bool victory) : m_result(victory), m_assetsLoaded(false) {}

EndState::~EndState() {
    m_music.Stop(0);
    objectArray.clear();
}

void EndState::LoadAssets() {
    if (m_assetsLoaded) return;
    m_assetsLoaded = true;
    auto* background = new GameObject();
    background->renderLayer = -1;
    auto* image = new SpriteRenderer(*background,
        m_result.playerVictory ? "resources/img/Win.png" : "resources/img/Lose.png");
    image->SetCameraFollower(true);
    background->AddComponent(image);
    AddObject(background);

    auto* prompt = new GameObject();
    prompt->renderLayer = 1;
    prompt->AddComponent(new Text(*prompt, "resources/font/neodgm.ttf", 27,
        Text::TextStyle::BLENDED, "ESPACO: JOGAR NOVAMENTE    ESC: SAIR",
        {255, 238, 184, 255}));
    prompt->box.x = (1200.0f - prompt->box.w) * 0.5f;
    prompt->box.y = 790.0f;
    AddObject(prompt);

    m_music.Open(m_result.playerVictory ? "resources/audio/endStateWin.ogg"
                                        : "resources/audio/endStateLose.ogg");
}

void EndState::Start() {
    if (started) return;
    Camera::Unfollow();
    Camera::pos = Vec2();
    LoadAssets();
    started = true;
    StartArray();
    m_music.Play(-1);
}

void EndState::Pause() { m_music.Stop(0); }
void EndState::Resume() { m_music.Play(-1); }

void EndState::Update(float dt) {
    const auto& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
        return;
    }
    if (input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
        return;
    }
    UpdateArray(dt);
}

void EndState::Render() { RenderArray(); }
