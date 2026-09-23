#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "SDL_include.h"
#include "TileSet.h"
#include "TileMap.h"

State::State() : m_quitRequested(false) {
    LoadAssets();
    m_music.Play(-1);

    // 1. Mapa de fundo
    GameObject* mapObj = new GameObject();
    mapObj->box.x = 0;
    mapObj->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    mapObj->AddComponent(new TileMap(*mapObj, "resources/map/map.txt", tileSet));
    AddObject(mapObj);

    // 2. Novos posicionamentos dos zumbis pelo cenário visível

    // Zumbi 1 - Campo aberto superior esquerdo
    GameObject* zombie1 = new GameObject();
    zombie1->box.x = 220;
    zombie1->box.y = 180;
    zombie1->AddComponent(new Zombie(*zombie1));
    AddObject(zombie1);

    // Zumbi 2 - Campo aberto superior central
    GameObject* zombie2 = new GameObject();
    zombie2->box.x = 680;
    zombie2->box.y = 220;
    zombie2->AddComponent(new Zombie(*zombie2));
    AddObject(zombie2);

    // Zumbi 3 - Lado de fora, à esquerda da cerca
    GameObject* zombie3 = new GameObject();
    zombie3->box.x = 380;
    zombie3->box.y = 620;
    zombie3->AddComponent(new Zombie(*zombie3));
    AddObject(zombie3);

    // Zumbi 4 - Dentro da arena de cerca, próximo ao gramado com flores
    GameObject* zombie4 = new GameObject();
    zombie4->box.x = 750;
    zombie4->box.y = 520;
    zombie4->AddComponent(new Zombie(*zombie4));
    AddObject(zombie4);
}

State::~State() {
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
    if (SDL_QuitRequested()) {
        m_quitRequested = true;
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    for (auto& obj : objectArray) {
        obj->Render();
    }
}

bool State::QuitRequested() const {
    return m_quitRequested;
}