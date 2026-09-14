#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "SDL_include.h"

// Note que SpriteRenderer vai requerer o include dele aqui em breve para o BG

State::State() : m_quitRequested(false) {
    LoadAssets(); // (Carrega a música aqui dentro como antes)
    m_music.Play(-1);

    // 1. Adicionando o Background como GameObject
    GameObject* bgObj = new GameObject();
    bgObj->AddComponent(new SpriteRenderer(*bgObj, "resources/img/Background.png"));
    AddObject(bgObj);

    // 2. Adicionando o Zombie como GameObject
    GameObject* zombieObj = new GameObject();
    zombieObj->box.x = 600;
    zombieObj->box.y = 450;
    zombieObj->AddComponent(new Zombie(*zombieObj));
    AddObject(zombieObj);
}

State::~State() {
    m_music.Stop(0);
    objectArray.clear(); // Limpa unique_ptrs
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

    // 1. Atualiza todos
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // 2. Remove os mortos (usando indices conforme especificado)
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--; // Compensa a remocao do elemento no array
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