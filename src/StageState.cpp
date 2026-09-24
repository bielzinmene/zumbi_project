#include "StageState.h"
#include "Camera.h"
#include "Character.h"
#include "Collider.h"
#include "Collision.h"
#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "TitleState.h"
#include "WaveSpawner.h"
#include <cmath>

StageState::StageState() : m_assetsLoaded(false) {
    Camera::Unfollow();
    Camera::pos = Vec2();
}

StageState::~StageState() {
    Camera::Unfollow();
    m_music.Stop(0);
    objectArray.clear();
}

void StageState::LoadAssets() {
    if (m_assetsLoaded) return;
    m_assetsLoaded = true;

    auto* background = new GameObject();
    background->renderLayer = -2;
    auto* sprite = new SpriteRenderer(*background, "resources/img/Background.png");
    sprite->SetCameraFollower(true);
    background->AddComponent(sprite);
    AddObject(background);

    auto* mapObject = new GameObject();
    mapObject->renderLayer = -1;
    auto* tiles = new TileSet(64, 64, "resources/img/Tileset.png");
    auto* map = new TileMap(*mapObject, "resources/map/map.txt", tiles);
    map->SetParallax(0, 0.8f);
    mapObject->AddComponent(map);
    AddObject(mapObject);

    auto* playerObject = new GameObject();
    playerObject->box.x = 1280.0f;
    playerObject->box.y = 1280.0f;
    playerObject->AddComponent(new PlayerController(*playerObject));
    auto* character = new Character(*playerObject, "resources/img/Player.png");
    playerObject->AddComponent(character);
    Character::player = character;
    m_player = AddObject(playerObject);
    Camera::Follow(playerObject);

    auto* waveObject = new GameObject();
    waveObject->AddComponent(new WaveSpawner(*waveObject));
    m_spawner = AddObject(waveObject);

    m_music.Open("resources/audio/BGM.wav");
}

void StageState::Start() {
    if (started) return;
    LoadAssets();
    started = true;
    StartArray();
    Camera::Update(0.0f);
    m_music.Play(-1);
}

void StageState::Pause() { m_music.Stop(0); }
void StageState::Resume() { m_music.Play(-1); }

void StageState::CheckCollisions() {
    for (const auto& object : objectArray) {
        if (!object->IsDead()) {
            if (auto* collider = object->GetComponent<Collider>()) collider->Update(0.0f);
        }
    }
    const float radians = static_cast<float>(std::acos(-1.0) / 180.0);
    for (size_t i = 0; i < objectArray.size(); ++i) {
        GameObject& first = *objectArray[i];
        if (first.IsDead()) continue;
        for (size_t j = i + 1; j < objectArray.size(); ++j) {
            if (first.IsDead() || !first.GetComponent<Collider>()) break;
            GameObject& second = *objectArray[j];
            if (second.IsDead()) continue;
            Collider* firstBox = first.GetComponent<Collider>();
            Collider* secondBox = second.GetComponent<Collider>();
            if (!firstBox || !secondBox) continue;
            if (IsColliding(firstBox->box, first.angleDeg * radians,
                            secondBox->box, second.angleDeg * radians)) {
                first.NotifyCollision(second);
                second.NotifyCollision(first);
            }
        }
    }
}

void StageState::RemoveDeadObjects() {
    for (size_t i = 0; i < objectArray.size();) {
        if (objectArray[i]->IsDead()) {
            if (Camera::GetFocus() == objectArray[i].get()) Camera::Unfollow();
            objectArray.erase(objectArray.begin() + i);
        } else {
            ++i;
        }
    }
}

void StageState::Update(float dt) {
    const auto& input = InputManager::GetInstance();
    if (input.QuitRequested()) {
        quitRequested = true;
        return;
    }
    if (input.KeyPress(ESCAPE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
        return;
    }
    if (!Camera::GetFocus()) Camera::Update(dt);
    UpdateArray(dt);
    CheckCollisions();
    RemoveDeadObjects();
    if (Camera::GetFocus()) Camera::Update(dt);

    const bool playerAlive = Character::player && Character::player->IsAlive();
    if (!playerAlive) {
        if (m_player.expired()) {
            popRequested = true;
            Game::GetInstance().Push(new EndState(false));
        }
    } else if (m_spawner.expired()) {
        popRequested = true;
        Game::GetInstance().Push(new EndState(true));
    }
}

void StageState::Render() { RenderArray(); }
