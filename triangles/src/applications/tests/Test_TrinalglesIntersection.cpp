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
    
    EXPECT_EQ(triangles::distance(point1, point2), 0.0);

    point1.setY(1.0);
    EXPECT_EQ(triangles::distance(point1, point2), 1.0);
    
    point2.setZ(1.0);
    EXPECT_NEAR(triangles::distance(point1, point2), std::sqrt(2.0), eps);
}

} // namespace UT