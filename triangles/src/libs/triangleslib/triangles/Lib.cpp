#include "Lib.h"

#include <algorithm>

namespace
{
    bool checkAllZeroes(std::array<float, 3> pointsToCheck)
    {
        constexpr float eps = 1.0e-6f;
        for (size_t i = 0; i < 3; ++i)
        {
            if (std::abs(pointsToCheck[i]) > eps)
            {
                return false;
            }
        }
        return true;
    }

    float getPoint(float p1, float p2, float d1, float d2)
    {
        float point = 0.0;
        if (p1 >= p2)
        {
            point = p2;
            if (d2 > d1)
            {
                point += (p1 - p2) * d2 / (d2 - d1);
            } 
            else
            {
                point += (p1 - p2) * d1 / (d1 - d2);
            }
        }
        else
        {
            point = p1;
            if (d2 > d1)
            {
                point += (p2 - p1) * d2 / (d2 - d1);
            } 
            else
            {
                point += (p2 - p1) * d1 / (d1 - d2);
            }
        }
        return point;
    }

    int sign(float num)
    {
        return static_cast<int>((num > 0) - (num < 0));
    }

    std::pair<float, float> getInterval(const std::array<float, 3>& projections, const std::array<float, 3>& distances)
    {
        if (sign(distances[0]) != sign(distances[1]) && sign(distances[0]) != sign(distances[2]))
        {
            return std::make_pair(getPoint(projections[0], projections[1], distances[0], distances[1]), getPoint(projections[0], projections[2], distances[0], distances[2]));
        }
        if (sign(distances[1]) != sign(distances[0]) && sign(distances[1]) != sign(distances[2]))
        {
            return std::make_pair(getPoint(projections[0], projections[1], distances[0], distances[1]), getPoint(projections[1], projections[2], distances[1], distances[2]));
        }
        return std::make_pair(getPoint(projections[0], projections[2], distances[0], distances[2]), getPoint(projections[1], projections[2], distances[1], distances[2]));
    }

    bool isOnPlainIntersection(const triangles::Triangle<3>& lhs, const triangles::Point<3>& someRhsPoint)
    {
       // Find redundant axis
       size_t axisToRemove = 0;
       for (axisToRemove = axisToRemove; axisToRemove < 3; ++axisToRemove)
       {
           if (someRhsPoint[axisToRemove] == lhs.getVertices()[0][axisToRemove])
           {
               break;
           }
       }
       return false;
    }
}

namespace triangles
{
    std::pair<bool, std::array<float, 3>> haveIntersectionWithPlane(const Triangle<3>& triangle, const Plane& otherPlane)
    {
        std::array<float, 3> distancesToOtherPlane{ otherPlane.getDistanceToPoint(triangle.getVertices()[0]), 
            otherPlane.getDistanceToPoint(triangle.getVertices()[1]), otherPlane.getDistanceToPoint(triangle.getVertices()[2]) };
        bool haveIntersection = true;
        if ((distancesToOtherPlane[0] > 0 && distancesToOtherPlane[1] > 0 && distancesToOtherPlane[2] > 0)
            || (distancesToOtherPlane[0] < 0 &&distancesToOtherPlane[1] < 0 && distancesToOtherPlane[2] < 0))
        {
            haveIntersection = false;
        }
        return std::make_pair(haveIntersection, distancesToOtherPlane);
    }

    bool edgeIntersect(const Edge<2>& lhs, const Edge<2>& rhs)
    {
        // Collinear or on one line
        if (isCollinear(lhs.getEdge(), rhs.getEdge()))
        {
            if (!isOneLineLying(lhs, rhs))
            {
                return false;
            }

            // Lying on one line then
            return haveIntersection(lhs, rhs);
        }

        //Decide whether they are cross vectors
        const auto delimeter = (lhs.getEdge() * crossProduct(Vector<2>(rhs.getEnd()), Vector<2>(rhs.getBegin())) - 
            rhs.getEdge() * crossProduct(Vector<2>(lhs.getEnd()), Vector<2>(lhs.getBegin()))) * ( 1.0f / crossProduct(rhs.getEdge(), lhs.getEdge()));

        if (dotProduct(delimeter - Vector<2>(lhs.getBegin()), delimeter - Vector<2>(lhs.getEnd())) <= 0
            && dotProduct(delimeter - Vector<2>(rhs.getBegin()), delimeter - Vector<2>(rhs.getEnd())) <= 0)
        {
            return true;
        }

        return false;
    }

    bool isNested(const Triangle<2>& lhs, const Point<2>& someRhsPoint)
    {   
        size_t j = 0;
        size_t k = 0;
        auto lhsVertices = lhs.getVertices();
        for (size_t i = 0; i < 3; ++i)
        {
            j = (i + 1) % 3;
            k = (i + 2) % 3;
            if (dotProduct(Vector<2>(lhsVertices[k], lhsVertices[j]) * Vector<2>(someRhsPoint, lhsVertices[j]), Vector<2>(lhsVertices[k], lhsVertices[j]) * Vector<2>(lhsVertices[i], lhsVertices[j])) < 0)
            {
                return false;
            }
        }

        return true;
    }

    bool isOnPlainIntersection(const Triangle<3>& lhs, const Point<3>& someRhsPoint)
    {
       // Find redundant axis
       size_t axisToRemove = 0;
       for (axisToRemove = axisToRemove; axisToRemove < 3; ++axisToRemove)
       {
           if (someRhsPoint[axisToRemove] == lhs.getVertices()[0][axisToRemove])
           {
               break;
           }
       }
       return isNested(lhs.project(axisToRemove), someRhsPoint.deleteAxis(axisToRemove));
    }

    bool haveIntersection(const Triangle<2>& lhs, const Triangle<2>& rhs)
    {
        // Check nesting of triangles - less operations 
        if (isNested(lhs, rhs.getVertices()[0]))
        {
            return true;
        }

        if (isNested(rhs, lhs.getVertices()[0]))
        {
            return true;
        }

        // Check edges intersection
        for (size_t i = 0; i < lhs.getEdges().size(); ++i)
        {
            for (size_t j = 0; j <  rhs.getEdges().size(); ++j)
            {
                if(edgeIntersect(lhs.getEdges()[i], rhs.getEdges()[j]))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool haveIntersection(const Triangle<3>& lhs, const Triangle<3>& rhs)
    {
        const auto [intersect1, lhsDistancesToRhs] = haveIntersectionWithPlane(lhs, getPlane(rhs));
        if (!intersect1)
        {
            return false;
        }

        const auto [intersect2, rhsDistancesToLhs] = haveIntersectionWithPlane(rhs, getPlane(lhs));
        if (!intersect2)
        {
            return false;
        }

        // Check that all zeroes;
        if (checkAllZeroes(lhsDistancesToRhs))
        {
            if (!checkAllZeroes(rhsDistancesToLhs))
            {
                throw std::runtime_error("Distances should all be zeroes in case of coplanar planes");
            }

            // Find the best suiting axis to project
            size_t axisToProject = 0;
            float biggestSquare = 0.0f;
            for(size_t i = 0; i < 3; ++i)
            {
                const auto currentSquare = lhs.project(i).square();
                axisToProject = currentSquare > biggestSquare ? i : axisToProject;
                biggestSquare = currentSquare > biggestSquare ? currentSquare : biggestSquare;
            }
            
            const auto lhsProjection = lhs.project(axisToProject);
            const auto rhsProjection = rhs.project(axisToProject);

            return haveIntersection(lhsProjection, rhsProjection);
        }

        // 3D part
        // Find intersection line L = O + tD, wher D = N1 * N2, O - some point on L
        const auto D = getPlane(lhs).getNormal() * getPlane(rhs).getNormal();

        // Project vertices of first triangle to L
        const auto p11 = dotProduct(D, Vector<3>(lhs.getVertices()[0]));
        const auto p12 = dotProduct(D, Vector<3>(lhs.getVertices()[1]));
        const auto p13 = dotProduct(D, Vector<3>(lhs.getVertices()[2]));
        
        const std::pair<float, float> intervalT1 = getInterval(std::array<float, 3>{ p11, p12, p13 }, lhsDistancesToRhs);

        // Project vertices of second triangle to L
        const auto p21 = dotProduct(D, Vector(rhs.getVertices()[0]));
        const auto p22 = dotProduct(D, Vector(rhs.getVertices()[1]));
        const auto p23 = dotProduct(D, Vector(rhs.getVertices()[2]));

        const std::pair<float, float> intervalT2 = getInterval(std::array<float, 3>{ p21, p22, p23 }, rhsDistancesToLhs);
        if (std::max(intervalT1.first, intervalT1.second) < std::min(intervalT2.first, intervalT2.second))
        {
            return false;
        }
        if (std::min(intervalT1.first, intervalT1.second) > std::max(intervalT2.first, intervalT2.second))
        {
            return false;
        }
        return true;
    }
}