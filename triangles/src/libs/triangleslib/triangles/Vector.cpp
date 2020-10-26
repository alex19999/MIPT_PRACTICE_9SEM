#include "Vector.h"

namespace triangles
{
    Vector<3> operator*(const Vector<3>& lhs, const Vector<3>& rhs)
    {
        return Vector<3>{ std::array<float, 3>{ lhs[1] * rhs[2] - rhs[1] * lhs[2],
            rhs[0] * lhs[2] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - rhs[0] * lhs[1] } };
    }

}