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

TEST(TestTree, SplayUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    EXPECT_EQ(tree.getRoot()->key, 2);
    
    tree.insert(8);
    EXPECT_EQ(tree.getRoot()->key, 8);
    EXPECT_EQ(tree.getRoot()->left->key, 2);
   
    tree.insert(7);
    EXPECT_EQ(tree.getRoot()->key, 7);
    EXPECT_EQ(tree.getRoot()->left->key, 2);
    EXPECT_EQ(tree.getRoot()->right->key, 8);
    
    tree.insert(-1);
    EXPECT_EQ(tree.getRoot()->key, -1);
    EXPECT_EQ(tree.getRoot()->right->key, 2);
    EXPECT_EQ(tree.getRoot()->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 8);
    
    // zig-zag and zig
    tree.insert(5);
    EXPECT_EQ(tree.getRoot()->key, 5);
    EXPECT_EQ(tree.getRoot()->right->key, 7);
    EXPECT_EQ(tree.getRoot()->left->key, -1);
    EXPECT_EQ(tree.getRoot()->right->right->key, 8);
    EXPECT_EQ(tree.getRoot()->left->right->key, 2);

    // zig-zig and zig
    tree.insert(-10);
    EXPECT_EQ(tree.getRoot()->key, -10);
    EXPECT_EQ(tree.getRoot()->right->key, -1);
    EXPECT_EQ(tree.getRoot()->right->right->key, 5);
    EXPECT_EQ(tree.getRoot()->right->right->left->key, 2);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->right->key, 8);

    tree.insert(3);
    EXPECT_EQ(tree.getRoot()->key, 3);
    EXPECT_EQ(tree.getRoot()->right->key, 5);
    EXPECT_EQ(tree.getRoot()->left->key, -1);
    EXPECT_EQ(tree.getRoot()->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 8);
    EXPECT_EQ(tree.getRoot()->left->right->key, 2);
    EXPECT_EQ(tree.getRoot()->left->left->key, -10);
        
    tree.insert(4);
    EXPECT_EQ(tree.getRoot()->key, 4);
    EXPECT_EQ(tree.getRoot()->right->key, 5);
    EXPECT_EQ(tree.getRoot()->left->key, 3);
    EXPECT_EQ(tree.getRoot()->left->left->key, -1);
    EXPECT_EQ(tree.getRoot()->left->left->left->key, -10);
    EXPECT_EQ(tree.getRoot()->left->left->right->key, 2);
    EXPECT_EQ(tree.getRoot()->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 8);

    // Remove leaf 
    tree.remove(-10);
    EXPECT_EQ(tree.getRoot()->key, 4);
    EXPECT_EQ(tree.getRoot()->right->key, 5);
    EXPECT_EQ(tree.getRoot()->left->key, 3);
    EXPECT_EQ(tree.getRoot()->left->left->key, -1);
    EXPECT_EQ(tree.getRoot()->left->left->right->key, 2);
    EXPECT_EQ(tree.getRoot()->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 8);

    // Remove non-leaf
    tree.remove(3);
    EXPECT_EQ(tree.getRoot()->key, 4);
    EXPECT_EQ(tree.getRoot()->left->key, -1);
    EXPECT_EQ(tree.getRoot()->left->right->key, 2);
    EXPECT_EQ(tree.getRoot()->right->key, 5);
    EXPECT_EQ(tree.getRoot()->right->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->right->key, 8);
}

TEST(TestTree, UpperBoundUnit)
{
    trees::SplayTree<int> tree{};

    // Insert values
    tree.insert(2);
    tree.insert(8);
    tree.insert(7);
    tree.insert(-1);
    tree.insert(-12);
    tree.insert(5);
    
    // Tree check
    EXPECT_EQ(tree.getRoot()->key, 5);
    EXPECT_EQ(tree.getRoot()->left->key, -1);
    EXPECT_EQ(tree.getRoot()->left->right->key, 2);
    EXPECT_EQ(tree.getRoot()->left->left->key, -12);
    EXPECT_EQ(tree.getRoot()->right->key, 7);
    EXPECT_EQ(tree.getRoot()->right->right->key, 8);
    
    EXPECT_EQ(tree.upperBound(4)->key, 5);
    EXPECT_EQ(tree.upperBound(5)->key, 5);
    EXPECT_EQ(tree.upperBound(0)->key, 2);
    EXPECT_EQ(tree.upperBound(-11)->key, -1);
    EXPECT_EQ(tree.upperBound(9), nullptr);
}

}