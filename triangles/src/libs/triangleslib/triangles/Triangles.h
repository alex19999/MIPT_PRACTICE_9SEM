#include <iostream>

namespace triangles
{
    class Point
    {
        float x;
        float y;
        float z;

    public:
        explicit Point(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0);

        // Getters
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }

        // Setters
        void setX(float x_) { x = x_; }
        void setY(float y_) { y = y_; }
        void setZ(float z_) { z = z_; }
    };

    float distance(const Point& p1, const Point& p2);

    class Triangle
    {
        Point vertice1;
        Point vertice2;
        Point vertice3;

    public:
        Triangle(Point vert1, Point vert2, Point vert3);
    };
}