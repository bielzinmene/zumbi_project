#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject; // Forward declaration

class Component {
protected:
    GameObject& associated;

public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};

#endif // COMPONENT_H