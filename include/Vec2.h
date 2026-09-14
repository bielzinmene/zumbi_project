#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    float x;
    float y;

    Vec2(float x = 0, float y = 0);

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(float scalar) const;

    float Magnitude() const;
    Vec2 Normalized() const;
    float Distance(const Vec2& target) const;
    float InclinationX() const;
    float InclinationBetween(const Vec2& target) const;
    void Rotate(float angleRad);
};

#endif // VEC2_H