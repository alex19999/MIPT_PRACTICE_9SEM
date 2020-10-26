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
    };

    template <size_t Dim>
    Edge<Dim>::Edge(Point<Dim> b, Point<Dim> e)
        : begin(b)
        , end(e)
        , edge(Vector<Dim>(end, begin))
    {
    }
}

#endif