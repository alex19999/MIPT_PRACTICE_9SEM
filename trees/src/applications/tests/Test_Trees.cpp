#include <gtest/gtest.h>
#include <trees/Tree.h>

namespace UT
{

TEST(TestTree, InsertUnit)
{
    trees::SplayNode<int> root{ 1 };

    // Insert values
    root.insert(2);
    root.insert(3);
    root.insert(0);
    root.insert(-1);
    root.insert(-3);
    root.insert(5);
    root.insert(-10);

    const auto result = root.print();
    EXPECT_EQ(result, std::string(" -10 -3 -1 0 1 2 3 5"));
}

TEST(TestTree, FindUnit)
{
    trees::SplayNode<int> root{ 1 };

    // Insert values
    root.insert(2);
    root.insert(8);
    root.insert(7);
    root.insert(-1);
    root.insert(-12);
    root.insert(5);
    root.insert(-10);

    EXPECT_EQ(root.find(2).first, true);
    EXPECT_EQ(root.find(-1).first, true);
    EXPECT_EQ(root.find(-21).first, false);
    EXPECT_EQ(root.find(-21).second, nullptr);
}

}