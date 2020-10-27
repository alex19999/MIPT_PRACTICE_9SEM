#include "Edge.h"

namespace triangles
{
    bool isOneLineLying(const Edge<2>& lhs, const Edge<2>& rhs, float eps)
    {
        return isCollinear(Vector<2>(lhs.getBegin(), rhs.getEnd()), lhs.getEdge(), eps);
    }
}