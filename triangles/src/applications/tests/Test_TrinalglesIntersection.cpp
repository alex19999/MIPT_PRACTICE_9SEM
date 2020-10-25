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
    const triangles::Point point1 { 1.0, 0.0, 0.0 };
    const triangles::Point point2 { 0.0, 1.0, 0.0 };
    const triangles::Point point3 { 0.0, 0.0, 1.0 };
    
    const triangles::Plane simplePlane{ point1, point2, point3 };

    EXPECT_EQ(simplePlane.getNormal()[0], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[1], 1.0);
    EXPECT_EQ(simplePlane.getNormal()[2], 1.0);
    EXPECT_EQ(simplePlane.getD(), -1.0);
}

TEST(TestVector, IncorrectTrianglesUnit)
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

} // namespace UT