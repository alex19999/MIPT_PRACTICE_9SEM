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

    bool isLyingOnSameLine(const Point& p1, const Point& p2, const float eps = 0.0000001);
    float getDistance(const Point& p1, const Point& p2);

    class Triangle
    {
        Point vertice1;
        Point vertice2;
        Point vertice3;

    public:
        Triangle(Point vert1, Point vert2, Point vert3);

        // Only getters with returning const& - after creating
        // triangle cannot be modified
        const Point& getVertice1() const { return vertice1; }
        const Point& getVertice2() const { return vertice2; }
        const Point& getVertice3() const { return vertice3; }
    };
}