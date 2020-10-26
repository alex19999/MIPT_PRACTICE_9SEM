#include <gtest/gtest.h>
#include <triangles/Triangle.h>

namespace UT
{

TEST(TestPlane, PlaneBuildingUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 1.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 0.0, 1.0, 0.0 }  };
    const triangles::Point<3> point13 { std::array<float, 3> { 0.0, 0.0, 1.0 }  };
    
    const triangles::Triangle<3> simpleTriangle{ point11, point12, point13 };
    const triangles::Plane simplePlane = getPlane(simpleTriangle);

    EXPECT_EQ(simplePlane.getNormal()[0], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[1], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[2], 1.0);
    EXPECT_EQ(simplePlane.getD(), -1.0);

    const triangles::Point<3> point21 { std::array<float, 3> { 1.0, 2.0, 3.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 2.0, 2.0, 2.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 31.0, -28.0, -11.0 } };
    
    const triangles::Triangle<3> triangle{ point21, point22, point23 };
    const triangles::Plane plane = getPlane(triangle);

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
    
    const triangles::Triangle<3> triangle{ point1, point2, point3 };
    const triangles::Plane plane = getPlane(triangle);
    
    const triangles::Point<3> testPoint1{ std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> testPoint2{ std::array<float, 3> { 1.0, 2.0, 3.0 } };
    const triangles::Point<3> testPoint3{ std::array<float, 3> { -3.0, 2.0, -1.0 } };

    EXPECT_NEAR(plane.getDistanceToPoint(testPoint1), -3.4909353369064853, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint2), -1.675648961715113, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint3), -6.8621814622618915, eps);
}

TEST(TestTriangle, SquareUnit)
{   
    const triangles::Point<3> point1 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point2 { std::array<float, 3> { 0.0, 4.0, 0.0 } };
    const triangles::Point<3> point3 { std::array<float, 3> { 3.0, 0.0, 0.0 } };
    
    EXPECT_EQ(triangles::Triangle<3>( point1, point2, point3 ).square(), 6.0f);
}

TEST(TestTriangle, ProjectUnit)
{   
    const triangles::Point<3> point1 { std::array<float, 3> { 0.0, 0.0, 1.0 } };
    const triangles::Point<3> point2 { std::array<float, 3> { 3.0, 0.0, 2.0 } };
    const triangles::Point<3> point3 { std::array<float, 3> { 1.5, 3.0, 0.0 } };
    
    const triangles::Triangle<3> triangle3D{ point1, point2, point3 };

    const auto triangle2D = triangle3D.project(0);
    EXPECT_EQ(triangle2D.getVertices()[0].getDims(), 2);
    EXPECT_EQ(triangle2D.getVertices()[1].getDims(), 2);
    EXPECT_EQ(triangle2D.getVertices()[2].getDims(), 2);

    EXPECT_EQ(triangle2D.getVertices()[0][0], 0.0);
    EXPECT_EQ(triangle2D.getVertices()[0][1], 1.0);
    EXPECT_EQ(triangle2D.getVertices()[1][0], 0.0);
    EXPECT_EQ(triangle2D.getVertices()[1][1], 2.0);
    EXPECT_EQ(triangle2D.getVertices()[2][0], 3.0);
    EXPECT_EQ(triangle2D.getVertices()[2][1], 0.0);
}

} // namespace UT