#include <gtest/gtest.h>
#include <triangles/Vector.h>

namespace UT
{

TEST(TestPoint, DistanceUnit)
{
    triangles::Point<3> p1 { std::array<float, 3> { 3.0, 0.0, 0.0} };
    triangles::Point<3> p2 { std::array<float, 3> { 0.0, 4.0, 0.0} };
    
    EXPECT_EQ(triangles::getDistance(p1, p2), 5.0);
}

TEST(TestPoint, MinusUnit)
{
    triangles::Point<3> p1 { std::array<float, 3> { 3.0, 2.0, 1.0} };
    triangles::Point<3> p2 { std::array<float, 3> { 1.0, 2.0, 3.0} };
    
    const auto p3 = p2 - p1;
    EXPECT_EQ(p3[0], -2.0);
    EXPECT_EQ(p3[1], 0.0);
    EXPECT_EQ(p3[2], 2.0);
}

}