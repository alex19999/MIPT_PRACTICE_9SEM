#include <iostream>
#include <vector>

#include "Vector.h"

// Follows http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
namespace triangles
{
    template <size_t Dim>
    class Plane
    {
        Vector<Dim> normal;
        float D;

    public:
        Plane(const Point<Dim>& p1, const Point<Dim>& p2, const Point<Dim>& p3);

        // Getters
        float getD() const { return D; };
        const Vector<Dim>& getNormal() const { return normal; }

        // Calculate distance to particular point
        float getDistanceToPoint(const Point<Dim>& p) const;
    };

    template <size_t Dim>
    Plane<Dim>::Plane(const Point<Dim>& p1, const Point<Dim>& p2, const Point<Dim>& p3)
    : normal(Vector<Dim>{ p2, p1 } * Vector<Dim>{ p3, p1 })
    , D(-dotProduct(normal, Vector<Dim>{ p1 }))
    {
    }

    template <size_t Dim>
    float Plane<Dim>::getDistanceToPoint(const Point<Dim>& p) const
    {
        return (dotProduct(normal, Vector<Dim>{p}) + D) / normal.getLength();
    }

    float getIntervalPoint(float p1, float p2, float d1, float d2);

    /*
    template <size_t Dim>
    class Triangle
    {
        Point vertice1;
        Point vertice2;
        Point vertice3;

        Plane<Dim> trianglePlane;

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