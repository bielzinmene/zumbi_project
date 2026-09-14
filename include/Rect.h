#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect(float x = 0, float y = 0, float w = 0, float h = 0);

    Rect operator+(const Vec2& offset) const;
    Vec2 Center() const;
    float Distance(const Rect& target) const;
    bool Contains(float pX, float pY) const;
    bool Contains(const Vec2& point) const;
};

#endif // RECT_H