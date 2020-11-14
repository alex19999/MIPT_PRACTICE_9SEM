#include <gtest/gtest.h>
#include <trees/Set.h>

namespace UT
{

TEST(TestSet, InsertUnit)
{
    trees::StandardSet<int> tree{};
    
    // Insert values
    tree.insert(2);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(5);
    tree.insert(-10);

    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(0));
    EXPECT_TRUE(tree.find(-1));
    EXPECT_TRUE(tree.find(-3));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(-10));
    EXPECT_FALSE(tree.find(11));
}

TEST(TestSet, RemoveUnit)
{
    trees::StandardSet<int> tree{};
    
    // Insert values
    tree.insert(2);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(5);
    tree.insert(-10);

    tree.remove(-10);
    tree.remove(5);
    tree.remove(-3);

    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(0));
    EXPECT_TRUE(tree.find(-1));
    EXPECT_FALSE(tree.find(-3));
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(-10));
    EXPECT_FALSE(tree.find(11));
}

TEST(TestSet, UpperBoundUnit)
{
    trees::StandardSet<int> tree{};
    
    // Insert values
    tree.insert(2);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(5);
    tree.insert(-10);

    EXPECT_EQ(*tree.upperBound(2), 3);
    EXPECT_EQ(*tree.upperBound(-10), -3);
    EXPECT_EQ(tree.upperBound(5), tree.end());
}

TEST(TestSet, LowerBoundUnit)
{
    trees::StandardSet<int> tree{};
    
    // Insert values
    tree.insert(2);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(5);
    tree.insert(-10);

    EXPECT_EQ(*tree.lowerBound(2), 2);
    EXPECT_EQ(*tree.lowerBound(1), 2);
    EXPECT_EQ(tree.lowerBound(6), tree.end());
}

TEST(TestSet, RangeQueryUnit)
{
    trees::StandardSet<int> tree{};
    
    // Insert values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    
    // Fully inside
    EXPECT_EQ(tree.rangeQuery(8, 31), 3u);
    
    // Fully outside
    EXPECT_EQ(tree.rangeQuery(6, 9), 0u);
    EXPECT_EQ(tree.rangeQuery(41, 42), 0u);

    // On boundaries
    EXPECT_EQ(tree.rangeQuery(8, 10), 0u);
    EXPECT_EQ(tree.rangeQuery(40, 45), 0u);

    // Cross
    EXPECT_EQ(tree.rangeQuery(8, 15), 1u);
    EXPECT_EQ(tree.rangeQuery(34, 85), 1u);
    EXPECT_EQ(tree.rangeQuery(20, 31), 1u);
    EXPECT_EQ(tree.rangeQuery(19, 30), 1u);
    EXPECT_EQ(tree.rangeQuery(20, 30), 0u);
}

}