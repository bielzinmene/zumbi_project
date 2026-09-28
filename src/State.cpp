#include "State.h"
#include <algorithm>

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() { objectArray.clear(); }

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
    if (!object) return {};
    auto existing = GetObjectPtr(object);
    if (!existing.expired()) return existing;
    auto added = std::shared_ptr<GameObject>(object);
    objectArray.push_back(added);
    if (started) added->Start();
    return added;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) const {
    for (const auto& entry : objectArray) {
        if (entry.get() == object) return entry;
    }
    return {};
}

bool State::PopRequested() const { return popRequested; }
bool State::QuitRequested() const { return quitRequested; }

void State::StartArray() {
    const size_t count = objectArray.size();
    for (size_t i = 0; i < count; ++i) objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
    const size_t count = objectArray.size();
    for (size_t i = 0; i < count; ++i) {
        auto object = objectArray[i];
        if (!object->IsDead()) object->Update(dt);
    }
}

void State::RenderArray() {
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
