#ifndef POINT_H
#define POINT_H

#include "Vector.h"

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
}

#endif