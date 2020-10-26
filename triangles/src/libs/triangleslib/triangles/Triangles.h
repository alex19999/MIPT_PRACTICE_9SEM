#include <iostream>
#include <vector>

#include "Vector.h"

// Follows http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
namespace triangles
{
    class Plane
    {
        Vector<3> normal;
        float D;

    public:
        Plane(const Vector<3>& normal, float D);

        // Getters
        float getD() const { return D; };
        const Vector<3>& getNormal() const { return normal; }

        // Calculate distance to particular point
        float getDistanceToPoint(const Point<3>& p) const;
    };

    Plane::Plane(const Vector<3>& normal, float D)
    : normal(normal)
    , D(D)
    {
    }

    float Plane::getDistanceToPoint(const Point<3>& p) const
    {
        return (dotProduct(normal, Vector<3>{p}) + D) / normal.getLength();
    }

    float getIntervalPoint(float p1, float p2, float d1, float d2);

    template <size_t Dim>
    class Segment
    {   
        Point<Dim> begin;
        Point<Dim> end;
        Vector<Dim> edge;
    
    public:
        Segment(Point<Dim> b, Point<Dim> e);
    };

    template <size_t Dim>
    Segment<Dim>::Segment(Point<Dim> b, Point<Dim> e)
        : begin(b)
        , end(e)
        , edge(Vector<Dim>(end, begin))
    {
    }

    template <size_t Dim>
    class Triangle
    {
        std::array<Point<Dim>, 3> vertices;
        std::array<Segment<Dim>, 3> edges;

    public:
        Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3);

        // Only getters
        const std::array<Point<Dim>, 3>& getVertices() const { return vertices; }
        const std::array<Segment<Dim>, 3>& getEdges() const { return edges; }

        float square() const;

        // In case of coplanars planes need to project triangle
        Triangle<Dim - 1> project(size_t axis) const;
    };

    template <size_t Dim>
    Triangle<Dim>::Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3)
    : vertices(std::array<Point<Dim>, 3> { vert1, vert2, vert3 })
    , edges(std::array<Segment<Dim>, 3> { Segment<Dim>(vert2, vert1), Segment<Dim>(vert3, vert2), Segment<Dim>(vert1, vert3) })
    {
        // Check lengthes of edges
        /*if (getDistance(vert1, vert2) + getDistance(vert1, vert3) <= getDistance(vert2, vert3) 
            || getDistance(vert1, vert2) + getDistance(vert2, vert3) <= getDistance(vert3, vert1)
            || getDistance(vert3, vert1) + getDistance(vert2, vert3) <= getDistance(vert1, vert2))
        {
            throw std::runtime_error("Cannot build triangle on these points: incorrect lengthes");
        }*/
    }

    template <size_t Dim>
    float Triangle<Dim>::square() const
    {
        return 0.5f * (Vector(vertices[1], vertices[0]) * Vector(vertices[2], vertices[0])).getLength();
    }

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

    template <size_t Dim>
    Triangle<Dim - 1> Triangle<Dim>::project(size_t axis) const
    {
        return Triangle<Dim - 1>{ vertices[0].deleteAxis(axis), vertices[1].deleteAxis(axis), vertices[2].deleteAxis(axis) };
    }

    Plane getPlane(const Triangle<3>& triangle);

    // Egde 2D intersect
    bool eddeIntersect(const Segment<2>& lhs, const Segment<2>& rhs);

    // 2D case
    bool haveIntersection(const Triangle<2>& lhs, const Triangle<2>& rhs);

    // 3D case
    bool haveIntersection(const Triangle<3>& lhs, const Triangle<3>& rhs);
}