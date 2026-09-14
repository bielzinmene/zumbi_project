#include "Rect.h"

Rect::Rect(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

Rect Rect::operator+(const Vec2& offset) const {
    return Rect(x + offset.x, y + offset.y, w, h);
}

Vec2 Rect::Center() const {
    return Vec2(x + (w / 2.0f), y + (h / 2.0f));
}

float Rect::Distance(const Rect& target) const {
    return Center().Distance(target.Center());
}

bool Rect::Contains(float pX, float pY) const {
    return (pX >= x && pX <= (x + w) && pY >= y && pY <= (y + h));
}

bool Rect::Contains(const Vec2& point) const {
    return Contains(point.x, point.y);
}