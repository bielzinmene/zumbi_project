#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include "PlayerController.h"
#include "WaveSpawner.h"
#include "Collider.h"
#include "Collision.h"
#include <algorithm>
#include <cmath>

State::State() : m_quitRequested(false), m_started(false), m_assetsLoaded(false) {
    Camera::Unfollow();
    Camera::pos = Vec2();
}

State::~State() {
    Camera::Unfollow();
    m_music.Stop(0);
    objectArray.clear();
}

void State::LoadAssets() {
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
    // os comandos chegam antes da atualizacao do personagem.
    playerObject->AddComponent(new PlayerController(*playerObject));
    auto* character = new Character(*playerObject, "resources/img/Player.png");
    playerObject->AddComponent(character);
    Character::player = character;
    AddObject(playerObject);
    Camera::Follow(playerObject);

    auto* waveObject = new GameObject();
    waveObject->AddComponent(new WaveSpawner(*waveObject));
    AddObject(waveObject);

    m_music.Open("resources/audio/BGM.wav");
    m_music.Play(-1);
}

void State::Start() {
    if (m_started) return;
    LoadAssets();
    m_started = true;
    const size_t count = objectArray.size();
    for (size_t i = 0; i < count; ++i) {
        auto object = objectArray[i];
        object->Start();
    }
    Camera::Update(0.0f);
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    if (!go) return {};
    auto existing = GetObjectPtr(go);
    if (!existing.expired()) return existing;
    auto object = std::shared_ptr<GameObject>(go);
    objectArray.push_back(object);
    if (m_started) object->Start();
    return object;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) const {
    for (const auto& object : objectArray) {
        if (object.get() == go) return object;
    }
    return {};
}

void State::Update(float dt) {
    const auto& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        m_quitRequested = true;
        return;
    }
    if (!Camera::GetFocus()) Camera::Update(dt);
    if (input.KeyPress(SPACE_KEY)) {
        auto* zombie = new GameObject();
        zombie->AddComponent(new Zombie(*zombie));
        zombie->box.x = input.GetMouseX() + Camera::pos.x;
        zombie->box.y = input.GetMouseY() + Camera::pos.y;
        AddObject(zombie);
    }
    // novos projeteis comecam a se mover no proximo frame.
    const size_t count = objectArray.size();
    for (size_t i = 0; i < count; ++i) {
        auto object = objectArray[i];
        if (!object->IsDead()) object->Update(dt);
    }

    // sincroniza as caixas apos todos os movimentos do frame.
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
    for (size_t i = 0; i < objectArray.size();) {
        if (objectArray[i]->IsDead()) {
            if (Camera::GetFocus() == objectArray[i].get()) Camera::Unfollow();
            objectArray.erase(objectArray.begin() + i);
        } else {
            ++i;
        }
    }
    if (Camera::GetFocus()) Camera::Update(dt);
}

void State::Render() {
    // ordena apenas o desenho, preservando a ordem de atualizacao.
    std::vector<GameObject*> visible;
    for (const auto& object : objectArray) {
        if (!object->IsDead()) visible.push_back(object.get());
    }
    std::stable_sort(visible.begin(), visible.end(), [](GameObject* a, GameObject* b) {
        if (a->renderLayer != b->renderLayer) return a->renderLayer < b->renderLayer;
        return a->GetRenderY() < b->GetRenderY();
    });
    for (auto* object : visible) object->Render();
}

bool State::QuitRequested() const { return m_quitRequested; }
