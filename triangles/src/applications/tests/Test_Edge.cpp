#include <gtest/gtest.h>
#include <triangles/Edge.h>

namespace UT
{

TEST(TestEdge, IsCollinearFalseUnit)
{
    triangles::Point<2> p11 { std::array<float, 2> { 3.0, 0.0} };
    triangles::Point<2> p12 { std::array<float, 2> { 4.0, 0.0} };

    triangles::Edge<2> edge1 { p11, p12 };

    triangles::Point<2> p21 { std::array<float, 2> { 9.0, 1.0} };
    triangles::Point<2> p22 { std::array<float, 2> { 6.0, 3.0} };
    
    triangles::Edge<2> edge2 { p21, p22 };

    EXPECT_FALSE(isOneLineLying(edge1, edge2));
}

TEST(TestEdge, IsCollinearTrueUnit)
{
    triangles::Point<2> p11 { std::array<float, 2> { 3.0, 0.0} };
    triangles::Point<2> p12 { std::array<float, 2> { 4.0, 0.0} };

    triangles::Edge<2> edge1 { p11, p12 };

    triangles::Point<2> p21 { std::array<float, 2> { 9.0, 0.0} };
    triangles::Point<2> p22 { std::array<float, 2> { 6.0, 0.0} };
    
    triangles::Edge<2> edge2 { p21, p22 };

    EXPECT_TRUE(isOneLineLying(edge1, edge2));
}

TEST(TestEdge, IsCollinearUnit)
{
    triangles::Point<2> p11 { std::array<float, 2> { 0.0, 0.0} };
    triangles::Point<2> p12 { std::array<float, 2> { 2.0, 1.0} };

    triangles::Edge<2> edge1 { p11, p12 };

    triangles::Point<2> p21 { std::array<float, 2> { 4.0, 2.0} };
    triangles::Point<2> p22 { std::array<float, 2> { 6.0, 3.0} };
    
    triangles::Edge<2> edge2 { p21, p22 };

    EXPECT_TRUE(isOneLineLying(edge1, edge2));
}

}