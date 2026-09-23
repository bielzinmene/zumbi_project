#include "GameObject.h"
#include <algorithm>

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    // percorre do fim para o inicio para evitar falhas de iterador
    for (int i = components.size() - 1; i >= 0; --i) {
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto* cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for (auto* cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    if (cpt != nullptr) {
        components.push_back(cpt);
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find(components.begin(), components.end(), cpt);
    if (it != components.end()) {
        components.erase(it);
    }
}