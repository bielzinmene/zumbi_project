#ifndef STATE_H
#define STATE_H

#include "GameObject.h"
#include <memory>
#include <vector>

class State {
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object) const;
    bool PopRequested() const;
    bool QuitRequested() const;

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    std::vector<std::shared_ptr<GameObject>> objectArray;
    bool popRequested;
    bool quitRequested;
    bool started;
};

#endif
