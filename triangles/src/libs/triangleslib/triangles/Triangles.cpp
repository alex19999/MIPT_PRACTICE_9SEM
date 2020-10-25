#include <cmath>
#include "Triangles.h"

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

    Triangle::Triangle(Point vert1, Point vert2, Point vert3)
    : vertice1(vert1)
    , vertice2(vert2)
    , vertice3(vert3)
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
}