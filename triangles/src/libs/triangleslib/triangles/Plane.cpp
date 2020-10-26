#include "Plane.h"

namespace triangles
{
    Plane::Plane(const Vector<3>& normal, float D)
    : normal(normal)
    , D(D)
    {
    }

    float Plane::getDistanceToPoint(const Point<3>& p) const
    {
        return (dotProduct(normal, Vector<3>{p}) + D) / normal.getLength();
    }
}