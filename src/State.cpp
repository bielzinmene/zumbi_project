#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"

State::State() : m_quitRequested(false) {
    Camera::Unfollow();
    Camera::pos = Vec2();
    LoadAssets();
    m_music.Play(-1);

    auto* background = new GameObject();
    auto* sprite = new SpriteRenderer(*background, "resources/img/Background.png");
    sprite->SetCameraFollower(true);
    background->AddComponent(sprite);
    AddObject(background);

    auto* mapObject = new GameObject();
    auto* tiles = new TileSet(64, 64, "resources/img/Tileset.png");
    auto* map = new TileMap(*mapObject, "resources/map/map.txt", tiles);
    // o fundo acompanha 80% do deslocamento; a camada superior acompanha 100%.
    map->SetParallax(0, 0.8f);
    mapObject->AddComponent(map);
    AddObject(mapObject);
}

State::~State() {
    Camera::Unfollow();
    m_music.Stop(0);
    objectArray.clear();
}

void State::LoadAssets() {
    m_music.Open("resources/audio/BGM.wav");
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}

void State::Update(float dt) {
    const auto& input = InputManager::GetInstance();
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        m_quitRequested = true;
        return;
    }
    Camera::Update(dt);
    if (input.KeyPress(SPACE_KEY)) {
        auto* zombie = new GameObject();
        zombie->AddComponent(new Zombie(*zombie));
        zombie->box.x = input.GetMouseX() + Camera::pos.x;
        zombie->box.y = input.GetMouseY() + Camera::pos.y;
        AddObject(zombie);
    }
    for (size_t i = 0; i < objectArray.size(); ++i) {
        objectArray[i]->Update(dt);
    }
    for (size_t i = 0; i < objectArray.size();) {
        if (objectArray[i]->IsDead()) {
            if (Camera::GetFocus() == objectArray[i].get()) Camera::Unfollow();
            objectArray.erase(objectArray.begin() + i);
        } else {
            ++i;
        }
    }
}

void State::Render() {
    // desenha o fundo fixo, as duas camadas do mapa e depois os zumbis.
    for (auto& object : objectArray) {
        object->Render();
    }
}

bool State::QuitRequested() const { return m_quitRequested; }
