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

    template <size_t Dim>
    class Triangle
    {
        std::array<Point<Dim>, 3> vertices;
        Plane<Dim> trianglePlane;

    public:
        Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3);

        // Only getters
        const std::array<Point<Dim>, 3>& getVertices() const { return vertices; }
        const Plane<Dim>& getPlane() const { return trianglePlane; }
        //bool hasIntersection(const Triangle& other) const;
    };

    template <size_t Dim>
    Triangle<Dim>::Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3)
    : vertices(std::array<Point<Dim>, Dim> { vert1, vert2, vert3 })
    , trianglePlane(Plane<Dim>(vert1, vert2, vert3))
    {
        // Check lengthes of edges
        if (getDistance(vert1, vert2) + getDistance(vert1, vert3) <= getDistance(vert2, vert3) 
            || getDistance(vert1, vert2) + getDistance(vert2, vert3) <= getDistance(vert3, vert1)
            || getDistance(vert3, vert1) + getDistance(vert2, vert3) <= getDistance(vert1, vert2))
        {
            throw std::runtime_error("Cannot build triangle on these points: incorrect lengthes");
        }
    }
}