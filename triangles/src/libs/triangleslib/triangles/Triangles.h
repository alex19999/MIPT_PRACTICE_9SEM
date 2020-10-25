#include <iostream>
#include <vector>

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

    class Vector
    {
        float a;
        float b;
        float c;

    public:
        
        explicit Vector(float a_ = 0.0, float b_ = 0.0, float c_ = 0.0);
        Vector(const Point& end, const Point& begin = Point{ 0.0, 0.0, 0.0 });
        
        // Getters
        float getA() const { return a; }
        float getB() const { return b; }
        float getC() const { return c; }

        float getLength() const;
        
    };

    // Dot Product
    float dotProduct(const Vector& lhs, const Vector& rhs);

    // Cross Product
    Vector operator*(const Vector& lhs, const Vector& rhs);
    
    // Common formula: A * x + B * y + C * z + D = 0, 
    // where n(A, B, C) - normal
    class Plane
    {
        Vector normal;
        float D;

    public:
        Plane(const Point& p1, const Point& p2, const Point& p3);

        // Getters
        float getD() const { return D; };
        std::vector<float> getNormal() const { return std::vector<float>{ normal.getA(), normal.getB(), normal.getC() }; }
    };

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