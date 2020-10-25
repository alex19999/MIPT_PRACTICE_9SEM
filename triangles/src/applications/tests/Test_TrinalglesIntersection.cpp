#include <gtest/gtest.h>
#include <triangles/Triangles.h>

namespace UT
{

TEST(TestPoints, GettersSettersUnit)
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

TEST(TestPoints, DistanceUnit)
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

TEST(TestPoints, IncorrectTrianglesUnit)
{   
    triangles::Point point11 { 1.0, 0.0, 0.0 };
    triangles::Point point12 { 2.0, 0.0, 0.0 };
    triangles::Point point13 { 3.0, 0.0, 0.0 };
    
    EXPECT_THROW(triangles::Triangle( point11, point12, point13 ), std::runtime_error);

    triangles::Point point21 { 2.0, 0.0, 0.0 };
    triangles::Point point22 { 2.0, 0.0, 0.0 };
    triangles::Point point23 { 18.0, 0.0, 0.0 };
    
    EXPECT_THROW(triangles::Triangle( point21, point22, point23 ), std::runtime_error);
}

} // namespace UT