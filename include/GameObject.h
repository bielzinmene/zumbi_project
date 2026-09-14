#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include "Rect.h"
#include "Component.h"

class GameObject {
private:
    std::vector<Component*> components;
    bool isDead;

public:
    Rect box;

    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead() const;
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    template <typename T>
    T* GetComponent() {
        for (auto* cpt : components) {
            T* specificCpt = dynamic_cast<T*>(cpt);
            if (specificCpt != nullptr) {
                return specificCpt;
            }
        }
        return nullptr;
    }
};

#endif // GAMEOBJECT_H