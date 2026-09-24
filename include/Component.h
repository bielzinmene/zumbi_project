#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject; // forward declaration

class Component {
protected:
    GameObject& associated;

public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};

#endif // component_h