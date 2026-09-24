#include "Collision.h"
#include <array>
#include <algorithm>
#include <cmath>

namespace {
using Corners = std::array<Vec2, 4>;

Corners RotatedCorners(const Rect& box, float angle) {
    const Vec2 center = box.Center();
    Corners points = {{Vec2(box.x, box.y), Vec2(box.x + box.w, box.y),
                       Vec2(box.x + box.w, box.y + box.h), Vec2(box.x, box.y + box.h)}};
    for (Vec2& point : points) {
        point = point - center;
        point.Rotate(angle);
        point = point + center;
    }
    return points;
}

bool SeparatedOn(const Corners& first, const Corners& second, const Vec2& axis) {
    auto dot = [&axis](const Vec2& point) { return point.x * axis.x + point.y * axis.y; };
    float firstMin = dot(first[0]);
    float firstMax = firstMin;
    float secondMin = dot(second[0]);
    float secondMax = secondMin;
    for (size_t i = 1; i < first.size(); ++i) {
        firstMin = std::min(firstMin, dot(first[i]));
        firstMax = std::max(firstMax, dot(first[i]));
        secondMin = std::min(secondMin, dot(second[i]));
        secondMax = std::max(secondMax, dot(second[i]));
    }
    return firstMax < secondMin || secondMax < firstMin;
}
}

bool IsColliding(const Rect& first, float firstAngle, const Rect& second, float secondAngle) {
    if (first.w <= 0.0f || first.h <= 0.0f || second.w <= 0.0f || second.h <= 0.0f) return false;
    const Corners a = RotatedCorners(first, firstAngle);
    const Corners b = RotatedCorners(second, secondAngle);
    const Vec2 axes[] = {a[1] - a[0], a[3] - a[0], b[1] - b[0], b[3] - b[0]};
    for (const Vec2& axis : axes) {
        if (SeparatedOn(a, b, axis)) return false;
    }
    return true;
}
