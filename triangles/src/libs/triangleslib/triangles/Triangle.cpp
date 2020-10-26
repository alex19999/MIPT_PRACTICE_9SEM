#include <cmath>
#include <array>
#include "Triangle.h"

namespace triangles
{
    Plane getPlane(const Triangle<3>& triangle)
    {
        const auto normal = Vector<3>(triangle.getVertices()[1], triangle.getVertices()[0]) * Vector<3>(triangle.getVertices()[2], triangle.getVertices()[0]);
        return Plane{ normal, -dotProduct(normal, Vector<3>{ triangle.getVertices()[0] }) };
    }
}