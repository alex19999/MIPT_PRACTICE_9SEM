#include "Vector.h"

namespace triangles
{
    bool isCollinear(const Vector<2>& lhs, const Vector<2>& rhs)
    {
        return (lhs[0] * rhs[1] - lhs[1] * rhs[0]) == 0.0f;
    }
    Vector<3> operator*(const Vector<3>& lhs, const Vector<3>& rhs)
    {
        return Vector<3>{ std::array<float, 3>{ lhs[1] * rhs[2] - rhs[1] * lhs[2],
            rhs[0] * lhs[2] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - rhs[0] * lhs[1] } };
    }

    Vector<3> operator*(const Vector<2>& lhs, const Vector<2>& rhs)
    {
        // Just orthogonal to lhs and rhs
        return Vector<3>{ std::array<float, 3>{ 0.0f, 0.0f, lhs[0] * rhs[1] - rhs[0] * lhs[1] } };
    }
}