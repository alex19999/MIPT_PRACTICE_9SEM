#ifndef EDGE_H
#define EDGE_H

#include "Vector.h"

namespace triangles
{
    template <size_t Dim>
    class Edge
    {   
        Point<Dim> begin;
        Point<Dim> end;
        Vector<Dim> edge;
    
    public:
        Edge(Point<Dim> b, Point<Dim> e);

        const Point<Dim>& getBegin() const { return begin; }
        const Point<Dim>& getEnd() const { return end; }
        const Vector<Dim>& getEdge() const { return edge; }
    };

    template <size_t Dim>
    Edge<Dim>::Edge(Point<Dim> b, Point<Dim> e)
        : begin(b)
        , end(e)
        , edge(Vector<Dim>(end, begin))
    {
    }

    bool isOneLineLying(const Edge<2>& lhs, const Edge<2>& rhs, float eps = 1.0e-8f);
}

#endif