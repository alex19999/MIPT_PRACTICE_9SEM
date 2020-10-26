#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <numeric>
#include <iostream>
#include <array>

namespace triangles
{
    template <size_t Dim>
    class Point
    {
    
        std::array<float, Dim> coordinates;

    public:
        explicit Point(const std::array<float, Dim>& coords);

        // Getter
        const float& operator[](size_t index) const { return coordinates[index]; }
        const std::array<float, Dim>& getCoordinates() const { return coordinates; }
        size_t getDims() const { return Dim; }

        Point<Dim - 1> deleteAxis(size_t axis) const;
    };

    template <size_t Dim>
    Point<Dim>::Point(const std::array<float, Dim>& cs)
        : coordinates(cs)
    {
    }

    template <size_t Dim>
    Point<Dim - 1> Point<Dim>::deleteAxis(size_t axis) const
    {
        std::array<float, Dim - 1> reducedPoint{};
        size_t j = 0;
        for(size_t i = 0; i < Dim; ++i)
        {
            if(i != axis)
            {
                reducedPoint[j++] = coordinates[i];
            }
        }
        return Point<Dim - 1>(reducedPoint);
    }

    template <size_t Dim>
    Point<Dim> operator-(const Point<Dim>& end, const Point<Dim>& begin)
    {
        std::array<float, Dim> coords;
        std::transform(end.getCoordinates().begin(), end.getCoordinates().end(), begin.getCoordinates().begin(), coords.begin(), std::minus<float>());
        return Point { coords };
    }

    template <size_t Dim>
    float getDistance(const Point<Dim>& p1, const Point<Dim>& p2)
    {
        float distance = 0.0f;
        for (size_t i = 0; i < Dim; ++i)
        {
            distance += (p1[i] - p2[i]) * (p1[i] - p2[i]);
        }
        return std::sqrt(distance);
    }

    template <size_t Dim>
    class Vector
    {
        std::array<float, Dim> points;
    public:
        Vector(const std::array<float, Dim>& points);
        Vector(const Point<Dim>& point);
        Vector(const Point<Dim>& end, const Point<Dim>& begin);

        float getLength() const;
        
        // Getters
        const float& operator[](size_t index) const { return points[index]; }
        size_t getDims() const { return Dim; }

        // iterators
        auto begin() { return points.begin(); }
        auto end() { return points.end(); }
        auto begin() const { return points.cbegin(); }
        auto end() const { return points.cend(); }
    };

    template <size_t Dim>
    Vector<Dim>::Vector(const std::array<float, Dim>& ps)
        : points(ps)
    {
    }

    template <size_t Dim>
    Vector<Dim>::Vector(const Point<Dim>& point)
        : points(point.getCoordinates())
    {
    }

    template <size_t Dim>
    Vector<Dim>::Vector(const Point<Dim>& end, const Point<Dim>& begin)
        : points((end - begin).getCoordinates())
    {
    }

    template <size_t Dim>
    float Vector<Dim>::getLength() const
    {
        float length = 0.0;
        for (size_t i = 0; i < Dim; ++i)
        {
            length += points[i] * points[i];
        }
        return std::sqrt(length);
    }
    
    template <size_t Dim>
    float dotProduct(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        return std::inner_product(std::begin(lhs), std::end(lhs), std::begin(rhs), 0.0f);
    }

    bool isCollinear(const Vector<2>& lhs, const Vector<2>& rhs);
    Vector<3> operator*(const Vector<3>& lhs, const Vector<3>& rhs);
    Vector<3> operator*(const Vector<2>& lhs, const Vector<2>& rhs);
}

#endif