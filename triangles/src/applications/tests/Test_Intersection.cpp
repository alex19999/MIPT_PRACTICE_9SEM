#include <gtest/gtest.h>
#include <triangles/Lib.h>

namespace UT
{

TEST(TestLib, NoPlaneIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 3.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 1.5, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 4.0, 0.0, 1.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 5.0, 0.0, 1.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 3.5, 0.0, 3.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_FALSE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarOnePointIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 4.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 2.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 4.0, 0.0, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 5.0, 2.0, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 6.0, 0.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_TRUE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarPartialIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 4.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 2.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 2.0, 0.0, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 5.0, 2.0, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 6.0, 0.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_TRUE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarInternalIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 4.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 2.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 1.0, 0.0, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 3.0, 0.0, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 2.0, 1.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_TRUE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarCrosslIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 3.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 1.5, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 4.0, 2.0, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 4.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_TRUE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarNestedlIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 5.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 2.5, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 1.0, 0.5, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 4.0, 0.5, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 2.5, 2.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_TRUE(haveIntersection(triangle1, triangle2));
}

TEST(TestLib, CoplanarNoIntersectionUnit)
{   
    const triangles::Point<3> point11 { std::array<float, 3> { 0.0, 0.0, 0.0 } };
    const triangles::Point<3> point12 { std::array<float, 3> { 2.0, 0.0, 0.0 } };
    const triangles::Point<3> point13 { std::array<float, 3> { 1.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { std::array<float, 3> { 4.0, 0.0, 0.0 } };
    const triangles::Point<3> point22 { std::array<float, 3> { 6.0, 0.0, 0.0 } };
    const triangles::Point<3> point23 { std::array<float, 3> { 5.0, 3.0, 0.0 } };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_FALSE(haveIntersection(triangle1, triangle2));
}

/*

TEST(TestLib, NoTrianglesIntersectionUnit)
{   
    const triangles::Point<3> point11 { 0.0, 0.0, 0.0 };
    const triangles::Point<3> point12 { 3.0, 0.0, 0.0 };
    const triangles::Point<3> point13 { 1.5, 3.0, 0.0 };
    
    triangles::Triangle<3> triangle1{ point11, point12, point13 };

    const triangles::Point<3> point21 { 4.0, 1.0, -1.0 };
    const triangles::Point<3> point22 { 5.0, 1.0, -1.0 };
    const triangles::Point<3> point23 { 6.0, 1.0, 3.0 };
    
    triangles::Triangle<3> triangle2{ point21, point22, point23 };

    EXPECT_FALSE(triangle1.hasIntersection(triangle2));
    EXPECT_FALSE(triangle2.hasIntersection(triangle1));
}

*/
}