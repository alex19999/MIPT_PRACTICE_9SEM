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

TEST(TestVector, MinusUnit)
{   
    const triangles::Vector<3> vec11 { std::array<float, 3>{ 1.0, 0.0, 0.0 } };
    const triangles::Vector<3> vec12 { std::array<float, 3>{ 0.0, 1.0, 0.0 } };
    
    const auto vec13 = vec11 - vec12;
    EXPECT_EQ(vec13[0], 1.0);
    EXPECT_EQ(vec13[1], -1.0);
    EXPECT_EQ(vec13[2], 0.0);

    const triangles::Vector<3> vec21 { std::array<float, 3>{ 1.0, 2.0, 3.0 } };
    const triangles::Vector<3> vec22 { std::array<float, 3>{ 3.0, 2.0, 1.0 } };
    
    const auto vec23 = vec21 - vec22;
    EXPECT_EQ(vec23[0], -2.0);
    EXPECT_EQ(vec23[1], 0.0);
    EXPECT_EQ(vec23[2], 2.0);
}

TEST(TestVector, MultiplyByUnit)
{   
    triangles::Vector<3> vec1 { std::array<float, 3>{ -1.0, 3.0, 4.0 } };

    vec1 *= 5.0;
    EXPECT_EQ(vec1[0], -5.0);
    EXPECT_EQ(vec1[1], 15.0);
    EXPECT_EQ(vec1[2], 20.0);

    vec1 *= 1.0f / 5.0f;
    EXPECT_EQ(vec1[0], -1.0);
    EXPECT_EQ(vec1[1], 3.0);
    EXPECT_EQ(vec1[2], 4.0);

    auto vec2 = vec1 * 1.5f;
    EXPECT_EQ(vec2[0], -1.5);
    EXPECT_EQ(vec2[1], 4.5);
    EXPECT_EQ(vec2[2], 6.0);
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

TEST(TestVector, CollinearUnit)
{   
    const triangles::Vector<2> vec11 { std::array<float, 2> { 1.0, 1.0 } };
    const triangles::Vector<2> vec12 { std::array<float, 2> { 2.0, 2.0 } };
    
    EXPECT_EQ(isCollinear(vec11, vec12), true);

    const triangles::Vector<2> vec21 { std::array<float, 2>{ 1.0, 0.0 } };
    const triangles::Vector<2> vec22 { std::array<float, 2>{ 0.0, 1.0 } };

    EXPECT_EQ(isCollinear(vec21, vec22), false);
}

}