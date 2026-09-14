#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if (mag == 0) return Vec2(0, 0);
    return Vec2(x / mag, y / mag);
}

float Vec2::Distance(const Vec2& target) const {
    return (*this - target).Magnitude();
}

float Vec2::InclinationX() const {
    return std::atan2(y, x);
}

float Vec2::InclinationBetween(const Vec2& target) const {
    return (target - *this).InclinationX();
}

void Vec2::Rotate(float angleRad) {
    float currentX = x;
    float currentY = y;
    x = currentX * std::cos(angleRad) - currentY * std::sin(angleRad);
    y = currentY * std::cos(angleRad) + currentX * std::sin(angleRad);
}