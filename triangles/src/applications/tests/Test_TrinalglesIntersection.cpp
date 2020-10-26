#include <gtest/gtest.h>
#include <triangles/Triangles.h>

namespace UT
{

TEST(TestPlane, PlaneBuildingUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 1.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 0.0, 1.0, 0.0 }  };
    const triangles::Point<3> point13 { std::array<float, 3> { 0.0, 0.0, 1.0 }  };
    
    const triangles::Plane<3> simplePlane{ point11, point12, point13 };

    EXPECT_EQ(simplePlane.getNormal()[0], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[1], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[2], 1.0);
    EXPECT_EQ(simplePlane.getD(), -1.0);

    const triangles::Point<3> point21 { std::array<float, 3> { 1.0, 2.0, 3.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 2.0, 2.0, 2.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 31.0, -28.0, -11.0 } };
    
    const triangles::Plane<3> plane{ point21, point22, point23 };

    EXPECT_EQ(plane.getNormal()[0], -30.0);
    EXPECT_EQ(plane.getNormal()[1], -16.0);
    EXPECT_EQ(plane.getNormal()[2], -30.0);
    EXPECT_EQ(plane.getD(), 152.0);
}

TEST(TestPlane, DistanceToPointUnit)
{
    constexpr double eps = 1.0e-6;
    const triangles::Point<3> point1 { std::array<float, 3> { 1.0, -12.0, 3.0 } };
    const triangles::Point<3> point2 { std::array<float, 3> { 11.0, 128.0, 23.0 } };
    const triangles::Point<3> point3 { std::array<float, 3> { -1.0, -2.0, 11.0 } };
    
    const triangles::Plane<3> plane{ point1, point2, point3 };
    
    const triangles::Point<3> testPoint1{ std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> testPoint2{ std::array<float, 3> { 1.0, 2.0, 3.0 } };
    const triangles::Point<3> testPoint3{ std::array<float, 3> { -3.0, 2.0, -1.0 } };

    EXPECT_NEAR(plane.getDistanceToPoint(testPoint1), -3.4909353369064853, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint2), -1.675648961715113, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint3), -6.8621814622618915, eps);
}

TEST(TestTriangle, IncorrectTrianglesUnit)
{   
    const triangles::Point<3> point1 { std::array<float, 3> { 2.0, 0.0, 0.0 } };
    const triangles::Point<3> point2 { std::array<float, 3> { 2.0, 0.0, 0.0 } };
    const triangles::Point<3> point3 { std::array<float, 3> { 18.0, 0.0, 0.0 } };
    
    EXPECT_THROW(triangles::Triangle<3>( point1, point2, point3 ), std::runtime_error);
}
/*
TEST(TestTriangle, NoPlaneIntersectionUnit)
{   
    const triangles::Point point11 { 0.0, 0.0, 0.0 };
    const triangles::Point point12 { 3.0, 0.0, 0.0 };
    const triangles::Point point13 { 1.5, 3.0, 0.0 };
    
    triangles::Triangle triangle1{ point11, point12, point13 };

    const triangles::Point point21 { 4.0, 0.0, 1.0 };
    const triangles::Point point22 { 5.0, 0.0, 1.0 };
    const triangles::Point point23 { 3.5, 0.0, 3.0 };
    
    triangles::Triangle triangle2{ point21, point22, point23 };

    EXPECT_FALSE(triangle1.hasIntersection(triangle2));
    EXPECT_FALSE(triangle2.hasIntersection(triangle1));
}

TEST(TestTriangle, NoTrianglesIntersectionUnit)
{   
    const triangles::Point point11 { 0.0, 0.0, 0.0 };
    const triangles::Point point12 { 3.0, 0.0, 0.0 };
    const triangles::Point point13 { 1.5, 3.0, 0.0 };
    
    triangles::Triangle triangle1{ point11, point12, point13 };

    const triangles::Point point21 { 4.0, 1.0, -1.0 };
    const triangles::Point point22 { 5.0, 1.0, -1.0 };
    const triangles::Point point23 { 6.0, 1.0, 3.0 };
    
    triangles::Triangle triangle2{ point21, point22, point23 };

    EXPECT_FALSE(triangle1.hasIntersection(triangle2));
    EXPECT_FALSE(triangle2.hasIntersection(triangle1));
}
*/
} // namespace UT