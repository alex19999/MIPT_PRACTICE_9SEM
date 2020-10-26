#include <iostream>
#include <vector>

// Follows http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
namespace triangles
{
    /*
    class Plane
    {
        Vector normal;
        float D;

    public:
        Plane(const Point& p1, const Point& p2, const Point& p3);

        // Getters
        float getD() const { return D; };
        const Vector& getNormal() const { return normal; }

        // Calculate distance to particular point
        float getDistanceToPoint(const Point& p) const;
    };

    float getIntervalPoint(float p1, float p2, float d1, float d2);

    template <size_t Dim>
    class Triangle
    {
        Point vertice1;
        Point vertice2;
        Point vertice3;

        Plane trianglePlane;

    public:
        Triangle(const Point<Dim>& vert1, const<Dim>& Point vert2, const Point<Dim>& vert3);

        // Only getters
        const Point& getVertice1() const { return vertice1; }
        const Point& getVertice2() const { return vertice2; }
        const Point& getVertice3() const { return vertice3; }

        const Plane& getPlane() const { return trianglePlane; }

        bool hasIntersection(const Triangle& other) const;
    };
    */
}