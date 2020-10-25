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

    float distance(const Point& p1, const Point& p2)
    {
        return std::sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX())
            + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY())
            + (p1.getZ() - p2.getZ()) * (p1.getZ() - p2.getZ()));
    }

    Triangle::Triangle(Point vert1, Point vert2, Point vert3)
    : vertice1(vert1)
    , vertice2(vert2)
    , vertice3(vert3)
    {
        if (distance(vertice1, vertice2) + distance(vertice1, vertice3) <= distance(vertice2, vertice3) 
            || distance(vertice1, vertice2) + distance(vertice2, vertice3) <= distance(vertice3, vertice1)
            || distance(vertice3, vertice1) + distance(vertice2, vertice3) <= distance(vertice1, vertice2))
        {
            throw std::runtime_error("Cannot build triangle on these points");
        }
    }
}