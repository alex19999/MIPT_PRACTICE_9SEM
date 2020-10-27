#include "Edge.h"

namespace triangles
{
    bool isOneLineLying(const Edge<2>& lhs, const Edge<2>& rhs, float eps)
    {
        return isCollinear(Vector<2>(lhs.getBegin(), rhs.getEnd()), lhs.getEdge(), eps);
    }

    bool haveIntersection(const Edge<2>& lhs, const Edge<2>& rhs)
    {
        if (dotProduct(Vector<2>(lhs.getEnd() - rhs.getEnd()), Vector<2>(lhs.getEnd() - rhs.getEnd())) <= 0)
        {
            return true;
        }
        if (dotProduct(Vector<2>(lhs.getBegin() - rhs.getEnd()), Vector<2>(lhs.getBegin() - rhs.getEnd())) <= 0)
        {
            return true;
        }
        if (dotProduct(Vector<2>(rhs.getBegin() - lhs.getBegin()), Vector<2>(rhs.getBegin() - lhs.getEnd())) <= 0)
        {
            return true;
        }
        if (dotProduct(Vector<2>(rhs.getEnd() - lhs.getBegin()), Vector<2>(rhs.getEnd() - lhs.getEnd())) <= 0)
        {
            return true;
        }

        return false;
    }
}