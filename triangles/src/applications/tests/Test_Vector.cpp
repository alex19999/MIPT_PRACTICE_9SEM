#include <gtest/gtest.h>
#include <triangles/Vector.h>

namespace UT
{

TEST(TestVector, LengthUnit)
{   
    const triangles::Vector<3> vec1 { std::array<float, 3>{ 1.0, 0.0, 0.0 } };
    EXPECT_EQ(vec1.getLength(), 1.0);

    const triangles::Vector<3> vec2 { std::array<float, 3>{ 3.0, 4.0, 0.0 } };
    EXPECT_EQ(vec2.getLength(), 5.0);
}

TEST(TestVector, CrossProductUnit)
{   
    const triangles::Vector<3> vec11 { std::array<float, 3>{ 1.0, 0.0, 0.0 } };
    const triangles::Vector<3> vec12 { std::array<float, 3>{ 0.0, 1.0, 0.0 } };
    
    const auto vec13 = vec11 * vec12;
    EXPECT_EQ(vec13[0], 0.0);
    EXPECT_EQ(vec13[1], 0.0);
    EXPECT_EQ(vec13[2], 1.0);

    const triangles::Vector<3> vec21 { std::array<float, 3>{ 1.0, 2.0, 3.0 } };
    const triangles::Vector<3> vec22 { std::array<float, 3>{ 3.0, 2.0, 1.0 } };
    
    const auto vec23 = vec21 * vec22;
    EXPECT_EQ(vec23[0], -4.0);
    EXPECT_EQ(vec23[1], 8.0);
    EXPECT_EQ(vec23[2], -4.0);
}

TEST(TestVector, DotProductUnit)
{   
    const triangles::Vector<2> vec11 { std::array<float, 2> { 1.0, 1.0 } };
    const triangles::Vector<2> vec12 { std::array<float, 2> { 2.0, 1.0 } };
    
    EXPECT_EQ(triangles::dotProduct(vec11, vec12), 3.0);

    const triangles::Vector<3> vec21 { std::array<float, 3>{ 1.0, 2.0, 3.0 } };
    const triangles::Vector<3> vec22 { std::array<float, 3>{ 3.0, 2.0, 1.0 } };

    EXPECT_EQ(triangles::dotProduct(vec21, vec22), 10.0);
}

}