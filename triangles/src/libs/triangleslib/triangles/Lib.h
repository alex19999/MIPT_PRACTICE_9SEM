#ifndef LIB_H
#define LIB_H

#include "Triangle.h"

namespace triangles
{
    std::pair<bool, std::array<float, 3>> haveIntersectionWithPlane(const Triangle<3>& triangle, const Plane& otherPlane);

    bool isOnPlainIntersection(const Triangle<3>& lhs, const Point<3>& someRhsPoint);
    
    // Are nested triangles
    bool isNested(const Triangle<2>& lhs, const Point<2>& someRhsPoint);

    // Egde 2D intersect
    bool eddeIntersect(const Edge<2>& lhs, const Edge<2>& rhs);

    // 2D case
    bool haveIntersection(const Triangle<2>& lhs, const Triangle<2>& rhs);

    // 3D case
    bool haveIntersection(const Triangle<3>& lhs, const Triangle<3>& rhs);
}

#endif