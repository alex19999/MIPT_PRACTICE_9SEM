#include <gtest/gtest.h>
#include <triangles/Triangles.h>

namespace UT
{

TEST(TestPoint, GettersSettersUnit)
{
    triangles::Point point;
    
    EXPECT_EQ(point.getX(), 0.0);
    EXPECT_EQ(point.getY(), 0.0);
    EXPECT_EQ(point.getZ(), 0.0);

    point.setX(1.0);
    point.setY(2.0);
    point.setZ(3.0);

    EXPECT_EQ(point.getX(), 1.0);
    EXPECT_EQ(point.getY(), 2.0);
    EXPECT_EQ(point.getZ(), 3.0);
}

TEST(TestPoint, DistanceUnit)
{   
    constexpr double eps = 1.0e-6;
    triangles::Point point1 { 1.0, 0.0, 0.0 };
    triangles::Point point2 { 1.0, 0.0, 0.0 };
    
    EXPECT_EQ(triangles::getDistance(point1, point2), 0.0);

    point1.setY(1.0);
    EXPECT_EQ(triangles::getDistance(point1, point2), 1.0);
    
    point2.setZ(1.0);
    EXPECT_NEAR(triangles::getDistance(point1, point2), std::sqrt(2.0), eps);
}

TEST(TestVector, CrossProductUnit)
{   
    const triangles::Vector vec11 { 1.0, 0.0, 0.0 };
    const triangles::Vector vec12 { 0.0, 1.0, 0.0 };
    
    const auto vec13 = vec11 * vec12;
    EXPECT_EQ(vec13.getA(), 0.0);
    EXPECT_EQ(vec13.getB(), 0.0);
    EXPECT_EQ(vec13.getC(), 1.0);

    const triangles::Vector vec21 { 1.0, 2.0, 3.0 };
    const triangles::Vector vec22 { 3.0, 2.0, 1.0 };
    
    const auto vec23 = vec21 * vec22;
    EXPECT_EQ(vec23.getA(), -4.0);
    EXPECT_EQ(vec23.getB(), 8.0);
    EXPECT_EQ(vec23.getC(), -4.0);
}

TEST(TestVector, DotProductUnit)
{   
    const triangles::Vector vec11 { 1.0, 0.0, 0.0 };
    const triangles::Vector vec12 { 0.0, 1.0, 0.0 };
    
    EXPECT_EQ(triangles::dotProduct(vec11, vec12), 0.0);

    const triangles::Vector vec21 { 1.0, 2.0, 3.0 };
    const triangles::Vector vec22 { 3.0, 2.0, 1.0 };
    
    EXPECT_EQ(triangles::dotProduct(vec21, vec22), 10.0);
}

TEST(TestPlane, PlaneBuildingUnit)
{   
    const triangles::Point point11 { 1.0, 0.0, 0.0 };
    const triangles::Point point12 { 0.0, 1.0, 0.0 };
    const triangles::Point point13 { 0.0, 0.0, 1.0 };
    
    const triangles::Plane simplePlane{ point11, point12, point13 };

    EXPECT_EQ(simplePlane.getNormal().getA(), 1.0);
    EXPECT_EQ(simplePlane.getNormal().getB(), 1.0);
    EXPECT_EQ(simplePlane.getNormal().getC(), 1.0);
    EXPECT_EQ(simplePlane.getD(), -1.0);

    const triangles::Point point21 { 1.0, 2.0, 3.0 };
    const triangles::Point point22 { 2.0, 2.0, 2.0 };
    const triangles::Point point23 { 31.0, -28.0, -11.0 };
    
    const triangles::Plane plane{ point21, point22, point23 };

    EXPECT_EQ(plane.getNormal().getA(), -30.0);
    EXPECT_EQ(plane.getNormal().getB(), -16.0);
    EXPECT_EQ(plane.getNormal().getC(), -30.0);
    EXPECT_EQ(plane.getD(), 152.0);
}

TEST(TestPlane, DistanceToPointUnit)
{
    constexpr double eps = 1.0e-6;
    const triangles::Point point1 { 1.0, -12.0, 3.0 };
    const triangles::Point point2 { 11.0, 128.0, 23.0 };
    const triangles::Point point3 { -1.0, -2.0, 11.0 };
    
    const triangles::Plane plane{ point1, point2, point3 };
    
    const triangles::Point testPoint1{ 0.0, 0.0, 0.0 };
    const triangles::Point testPoint2{ 1.0, 2.0, 3.0 };
    const triangles::Point testPoint3{ -3.0, 2.0, -1.0 };

    EXPECT_NEAR(plane.getDistanceToPoint(testPoint1), -3.4909353369064853, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint2), -1.675648961715113, eps);
    EXPECT_NEAR(plane.getDistanceToPoint(testPoint3), -6.8621814622618915, eps);
}

TEST(TestTriangle, IncorrectTrianglesUnit)
{   
    const triangles::Point point11 { 1.0, 0.0, 0.0 };
    const triangles::Point point12 { 2.0, 0.0, 0.0 };
    const triangles::Point point13 { 3.0, 0.0, 0.0 };
    
    EXPECT_THROW(triangles::Triangle( point11, point12, point13 ), std::runtime_error);

    const triangles::Point point21 { 2.0, 0.0, 0.0 };
    const triangles::Point point22 { 2.0, 0.0, 0.0 };
    const triangles::Point point23 { 18.0, 0.0, 0.0 };
    
    EXPECT_THROW(triangles::Triangle( point21, point22, point23 ), std::runtime_error);
}

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

} // namespace UT