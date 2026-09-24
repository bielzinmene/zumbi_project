#include "GameObject.h"
#include "Camera.h"
#include <algorithm>

GameObject::GameObject()
    : isDead(false), angleDeg(0.0), started(false), renderLayer(0), renderOffsetY(0.0f) {}

GameObject::~GameObject() {
    if (Camera::GetFocus() == this) Camera::Unfollow();
    for (auto it = components.rbegin(); it != components.rend(); ++it) delete *it;
}

void GameObject::Start() {
    if (started) return;
    started = true;
    const size_t count = components.size();
    for (size_t i = 0; i < count; ++i) components[i]->Start();
}

float GameObject::GetRenderY() const {
    return box.y + box.h + renderOffsetY;
}

void GameObject::Update(float dt) {
    const size_t count = components.size();
    for (size_t i = 0; i < count; ++i) components[i]->Update(dt);
}

void GameObject::Render() {
    for (auto* component : components) component->Render();
}

bool GameObject::IsDead() const { return isDead; }
void GameObject::RequestDelete() { isDead = true; }

void GameObject::AddComponent(Component* component) {
    if (!component) return;
    components.push_back(component);
    if (started) component->Start();
}

void GameObject::RemoveComponent(Component* component) {
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end()) {
        components.erase(it);
        delete component;
    }
}

void GameObject::NotifyCollision(GameObject& other) {
    const auto listeners = components;
    for (Component* listener : listeners) {
        if (std::find(components.begin(), components.end(), listener) != components.end()) {
            listener->NotifyCollision(other);
        }
    }
}
