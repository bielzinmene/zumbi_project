#ifndef CAMERA_H
#define CAMERA_H
#include "Vec2.h"
class GameObject;

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static GameObject* GetFocus();
    static Vec2 pos;
    static Vec2 speed;
private:
    static GameObject* s_focus;
};
#endif
