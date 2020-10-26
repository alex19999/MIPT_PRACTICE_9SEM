#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <numeric>
#include <iostream>
#include <array>

namespace triangles
{
    template <size_t Dim>
    class Vector
    {
        std::array<float, Dim> points;
    public:
        Vector(const std::array<float, Dim>& points);
        
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

    Vector<3> operator*(const Vector<3>& lhs, const Vector<3>& rhs);
}

#endif