#ifndef LIB_H
#define LIB_H

#include "Triangle.h"

namespace triangles
{
    float getIntervalPoint(float p1, float p2, float d1, float d2);

    std::pair<bool, std::array<float, 3>> haveIntersectionWithPlane(const Triangle<3>& triangle, const Plane& otherPlane);

    // Egde 2D intersect
    bool eddeIntersect(const Edge<2>& lhs, const Edge<2>& rhs);

    // 2D case
    bool haveIntersection(const Triangle<2>& lhs, const Triangle<2>& rhs);

    // 3D case
    bool haveIntersection(const Triangle<3>& lhs, const Triangle<3>& rhs);
}

#endif