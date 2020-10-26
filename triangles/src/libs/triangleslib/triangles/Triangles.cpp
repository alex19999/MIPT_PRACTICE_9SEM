#include <cmath>
#include <array>
#include "Triangles.h"
/*
namespace triangles
{
    Point::Point(float x_, float y_, float z_)
    : x(x_)
    , y(y_)
    , z(z_)
    {
    }

    bool isLyingOnSameLine(const Point& p1, const Point& p2, const float eps)
    {
        return (std::abs(p1.getX() - p2.getX()) < eps && std::abs(p1.getY() - p2.getY()) < eps)
            || (std::abs(p1.getY() - p2.getY()) < eps && std::abs(p1.getZ() - p2.getZ()) < eps)
            || (std::abs(p1.getZ() - p2.getZ()) < eps && std::abs(p1.getX() - p2.getX()) < eps);
    }

    float getDistance(const Point& p1, const Point& p2)
    {
        return std::sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX())
            + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY())
            + (p1.getZ() - p2.getZ()) * (p1.getZ() - p2.getZ()));
    }

    Vector::Vector(float a_, float b_, float c_)
    : a(a_)
    , b(b_)
    , c(c_)
    {
    }

    Vector::Vector(const Point& end, const Point& begin)
    : a(end.getX() - begin.getX())
    , b(end.getY() - begin.getY())
    , c(end.getZ() - begin.getZ())
    {
    }

    float Vector::getLength() const
    {
        return std::sqrt(a * a + b * b + c * c);
    }

    Vector operator*(const Vector& lhs, const Vector& rhs)
    {
        return Vector{ lhs.getB() * rhs.getC() - rhs.getB() * lhs.getC(),
            rhs.getA() * lhs.getC() - lhs.getA() * rhs.getC(),
            lhs.getA() * rhs.getB() - rhs.getA() * lhs.getB() };
    }

    float dotProduct(const Vector& lhs, const Vector& rhs)
    {
        return lhs.getA() * rhs.getA() + lhs.getB() * rhs.getB() + lhs.getC() * rhs.getC();
    }

    Plane::Plane(const Point& p1, const Point& p2, const Point& p3)
    : normal(Vector{ p2, p1 } * Vector{ p3, p1 })
    , D(-dotProduct(normal, Vector{ p1 }))
    {
    }

    float Plane::getDistanceToPoint(const Point& p) const
    {
        return (dotProduct(normal, Vector{p}) + D) / normal.getLength();
    }

    Triangle::Triangle(Point vert1, Point vert2, Point vert3)
    : vertice1(vert1)
    , vertice2(vert2)
    , vertice3(vert3)
    , trianglePlane(Plane(vert1, vert2, vert3))
    {
        // Check that not lying on the same line
        if (isLyingOnSameLine(vertice1, vertice2) && isLyingOnSameLine(vertice2, vertice3))
        {
            throw std::runtime_error("Cannot build triangle on these points: all points are lying on same line");
        }

        // Check lengthes of edges
        if (getDistance(vertice1, vertice2) + getDistance(vertice1, vertice3) <= getDistance(vertice2, vertice3) 
            || getDistance(vertice1, vertice2) + getDistance(vertice2, vertice3) <= getDistance(vertice3, vertice1)
            || getDistance(vertice3, vertice1) + getDistance(vertice2, vertice3) <= getDistance(vertice1, vertice2))
        {
            throw std::runtime_error("Cannot build triangle on these points: incorrect lengthes");
        }
    }

    bool Triangle::hasIntersection(const Triangle& other) const
    {
        std::array<float, 3> distancesToOtherPoints{ trianglePlane.getDistanceToPoint(other.getVertice1()), 
            trianglePlane.getDistanceToPoint(other.getVertice2()), trianglePlane.getDistanceToPoint(other.getVertice3()) };
        if ((distancesToOtherPoints[0] > 0 && distancesToOtherPoints[1] > 0 && distancesToOtherPoints[2] > 0)
            || (distancesToOtherPoints[0] < 0 && distancesToOtherPoints[1] < 0 && distancesToOtherPoints[2] < 0))
        {
            return false;
        }

        const auto otherPlane = other.getPlane();
        std::array<float, 3> distancesToOtherPlane{ otherPlane.getDistanceToPoint(vertice1), 
            otherPlane.getDistanceToPoint(vertice2), otherPlane.getDistanceToPoint(vertice3) };
        if ((distancesToOtherPlane[0] > 0 && distancesToOtherPlane[1] > 0 && distancesToOtherPlane[2] > 0)
            || (distancesToOtherPlane[0] < 0 && distancesToOtherPlane[1] < 0 && distancesToOtherPlane[2] < 0))
        {
            return false;
        }

        // Find intersection line L = O + tD, wher D = N1 * N2, O - some point on L
        const auto D = trianglePlane.getNormal() * otherPlane.getNormal();

        // Project vertices of first triangle to L
        const auto p11 = dotProduct(D, Vector(vertice1));
        const auto p12 = dotProduct(D, Vector(vertice2));
        const auto p13 = dotProduct(D, Vector(vertice3));

        std::array<float, 2> intervalT1;
        size_t index = 0;
        if (distancesToOtherPlane[0] * distancesToOtherPlane[1] < 0)
        {
            intervalT1[index] = getIntervalPoint(p11, p12, distancesToOtherPlane[0], distancesToOtherPlane[1]);
            index += 1;
        }
        if (distancesToOtherPlane[0] * distancesToOtherPlane[2] < 0)
        {
            intervalT1[index] = getIntervalPoint(p11, p13, distancesToOtherPlane[0], distancesToOtherPlane[2]);
            index += 1;
        }
        if (distancesToOtherPlane[1] * distancesToOtherPlane[2] < 0)
        {
            intervalT1[index] = getIntervalPoint(p12, p13, distancesToOtherPlane[1], distancesToOtherPlane[2]);
        }

        // Project vertices of second triangle to L
        const auto p21 = dotProduct(D, Vector(other.getVertice1()));
        const auto p22 = dotProduct(D, Vector(other.getVertice2()));
        const auto p23 = dotProduct(D, Vector(other.getVertice3()));

        std::array<float, 2> intervalT2;
        index = 0;
        if (distancesToOtherPoints[0] * distancesToOtherPoints[1] < 0)
        {
            intervalT2[index] = getIntervalPoint(p21, p22, distancesToOtherPoints[0], distancesToOtherPoints[1]);
            index += 1;
        }
        if (distancesToOtherPoints[0] * distancesToOtherPoints[2] < 0)
        {
            intervalT2[index] = getIntervalPoint(p21, p23, distancesToOtherPoints[0], distancesToOtherPoints[2]);
            index += 1;
        }
        if (distancesToOtherPoints[1] * distancesToOtherPoints[2] < 0)
        {
            intervalT2[index] = getIntervalPoint(p22, p23, distancesToOtherPoints[1], distancesToOtherPoints[2]);
        }
        if (std::max(intervalT1[0], intervalT1[1]) < std::min(intervalT2[0], intervalT2[1]))
        {
            return false;
        }
        if (std::min(intervalT1[0], intervalT1[1]) > std::max(intervalT2[0], intervalT2[1]))
        {
            return false;
        }
        std::cout << intervalT1[0] << " " << intervalT1[1] << std::endl;
        std::cout << intervalT2[0] << " " << intervalT2[1] << std::endl;
        return true;
    }

    float getIntervalPoint(float p1, float p2, float d1, float d2)
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
}
*/