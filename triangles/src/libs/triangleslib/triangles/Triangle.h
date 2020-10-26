#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>

#include "Vector.h"
#include "Plane.h"
#include "Edge.h"

// Follows http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf

namespace triangles
{
    float getIntervalPoint(float p1, float p2, float d1, float d2);

    template <size_t Dim>
    class Triangle
    {
        std::array<Point<Dim>, 3> vertices;
        std::array<Edge<Dim>, 3> edges;

    public:
        Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3);

        // Only getters
        const std::array<Point<Dim>, 3>& getVertices() const { return vertices; }
        const std::array<Edge<Dim>, 3>& getEdges() const { return edges; }

        float square() const;

        // In case of coplanars planes need to project triangle
        Triangle<Dim - 1> project(size_t axis) const;
    };

    template <size_t Dim>
    Triangle<Dim>::Triangle(const Point<Dim>& vert1, const Point<Dim>& vert2, const Point<Dim>& vert3)
    : vertices(std::array<Point<Dim>, 3> { vert1, vert2, vert3 })
    , edges(std::array<Edge<Dim>, 3> { Edge<Dim>(vert2, vert1), Edge<Dim>(vert3, vert2), Edge<Dim>(vert1, vert3) })
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

    template <size_t Dim>
    Triangle<Dim - 1> Triangle<Dim>::project(size_t axis) const
    {
        return Triangle<Dim - 1>{ vertices[0].deleteAxis(axis), vertices[1].deleteAxis(axis), vertices[2].deleteAxis(axis) };
    }

        Plane getPlane(const Triangle<3>& triangle);
}

#endif