#include <gtest/gtest.h>
#include <trees/Tree.h>

namespace UT
{

TEST(TestTree, InsertUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(5);
    tree.insert(-10);

    // Repeat
    tree.insert(0);
    tree.insert(-10);

    const auto result = tree.print(tree.getRoot());
    EXPECT_EQ(result, std::string(" -10 -3 -1 0 2 3 5"));
}

TEST(TestTree, FindUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    tree.insert(-10);

    EXPECT_EQ(tree.find(2), true);
    EXPECT_EQ(tree.find(-1), true);
    EXPECT_EQ(tree.find(-21), false);
}

TEST(TestTree, RemoveLeafUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    tree.insert(-10);

    tree.remove(-10);
    
    const auto result = tree.print(tree.getRoot());
    EXPECT_EQ(result, std::string(" -12 -1 2 5 7 8"));
}

TEST(TestTree, RemoveNonLeafUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    tree.insert(-10);

    tree.remove(-12);
    const auto result = tree.print(tree.getRoot());
    EXPECT_EQ(result, std::string(" -10 -1 2 5 7 8"));
}

TEST(TestTree, RemoveRootUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    tree.insert(-10);

    tree.remove(2);
    const auto result = tree.print(tree.getRoot());
    EXPECT_EQ(result, std::string(" -12 -10 -1 5 7 8"));
}

TEST(TestTree, NoRemoveUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    tree.insert(-10);

    tree.remove(21);
    const auto result = tree.print(tree.getRoot());
    EXPECT_EQ(result, std::string(" -12 -10 -1 2 5 7 8"));
}

}