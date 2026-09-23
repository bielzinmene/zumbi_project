#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "SDL_include.h"
#include "TileSet.h"
#include "TileMap.h"

State::State() : m_quitRequested(false) {
    LoadAssets(); //carega musica
    m_music.Play(-1);

    // mapa adicionado primeiro (fundo)
    GameObject* mapObj = new GameObject();
    mapObj->box.x = 0;
    mapObj->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    mapObj->AddComponent(new TileMap(*mapObj, "resources/map/map.txt", tileSet));
    AddObject(mapObj);

    // zumbi adicionado em seguida (frente)
    GameObject* zombieObj = new GameObject();
    zombieObj->box.x = 600;
    zombieObj->box.y = 450;
    zombieObj->AddComponent(new Zombie(*zombieObj));
    AddObject(zombieObj);
}

State::~State() {
    m_music.Stop(0);
    objectArray.clear(); // limpa unique_ptrs
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

    // atualiza todos
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // remove os mortos
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--; // comepensa a remocao do elemento no array
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