#include <gtest/gtest.h>

#include <vector>

#include "bst.h"

TEST(Add, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {0};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Add, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {1, 2, 3, 4, 5};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Add, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {1, 3, 2, 5, 4};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Remove, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    bst.remove(0);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Remove, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    bst.remove(1);
    bst.remove(3);
    std::vector<BST<int>::Node *> nodes;
    bst.preorderTraversal(nodes);
    std::vector<int> preorder = {2, 4, 5};
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Remove, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    bst.remove(3);
    bst.remove(5);
    std::vector<BST<int>::Node *> nodes;
    bst.preorderTraversal(nodes);
    std::vector<int> preorder = {1, 4, 2};
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Find, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    BST<int>::Node *node = bst.find(0);
    ASSERT_EQ(node->getParent(), nullptr);
    ASSERT_EQ(node->getLeft(), nullptr);
    ASSERT_EQ(node->getRight(), nullptr);
}

TEST(Find, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    BST<int>::Node *node = bst.find(2);
    ASSERT_EQ(node->getParent()->getKey(), 1);
    ASSERT_EQ(node->getLeft(), nullptr);
    ASSERT_EQ(node->getRight()->getKey(), 3);
    node = bst.find(4);
    ASSERT_EQ(node->getParent()->getKey(), 3);
    ASSERT_EQ(node->getLeft(), nullptr);
    ASSERT_EQ(node->getRight()->getKey(), 5);
}

TEST(Find, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    BST<int>::Node *node = bst.find(3);
    ASSERT_EQ(node->getParent()->getKey(), 1);
    ASSERT_EQ(node->getLeft()->getKey(), 2);
    ASSERT_EQ(node->getRight()->getKey(), 5);
    node = bst.find(5);
    ASSERT_EQ(node->getParent()->getKey(), 3);
    ASSERT_EQ(node->getLeft()->getKey(), 4);
    ASSERT_EQ(node->getRight(), nullptr);
}

TEST(Traverse, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> inorder = {0};
    std::vector<int> preorder = {0};
    std::vector<int> postorder = {0};
    bst.inorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), inorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), inorder[i]);
    }
    nodes.clear();
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
    nodes.clear();
    bst.postorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), postorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), postorder[i]);
    }
}

TEST(Traverse, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> inorder = {1, 2, 3, 4, 5};
    std::vector<int> preorder = {1, 2, 3, 4, 5};
    std::vector<int> postorder = {5, 4, 3, 2, 1};
    bst.inorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), inorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), inorder[i]);
    }
    nodes.clear();
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
    nodes.clear();
    bst.postorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), postorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), postorder[i]);
    }
}

TEST(Traverse, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> inorder = {1, 2, 3, 4, 5};
    std::vector<int> preorder = {1, 3, 2, 5, 4};
    std::vector<int> postorder = {2, 4, 5, 3, 1};
    bst.inorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), inorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), inorder[i]);
    }
    nodes.clear();
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
    nodes.clear();
    bst.postorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), postorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), postorder[i]);
    }
}

TEST(Subtree, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    BST<int> subbst;
    subbst.add(3);
    subbst.add(1);
    subbst.add(2);
    bst.insertSubtree(subbst);
    bst.removeSubtree(1);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {0, 3};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Subtree, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    BST<int> subbst;
    subbst.add(6);
    subbst.add(3);
    subbst.add(0);
    bst.insertSubtree(subbst);
    bst.removeSubtree(1);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Subtree, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    BST<int> subbst;
    subbst.add(2);
    subbst.add(-1);
    subbst.add(6);
    subbst.add(0);
    subbst.add(7);
    bst.insertSubtree(subbst);
    bst.removeSubtree(3);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {1, -1, 0};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Branch, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    bst.removeBranch(0);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Branch, test_2)
{
    BST<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);
    bst.removeBranch(3);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {1, 2};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(Branch, test_3)
{
    BST<int> bst;
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(2);
    bst.add(-1);
    bst.add(0);
    bst.add(6);
    bst.add(7);
    bst.removeBranch(5);
    std::vector<BST<int>::Node *> nodes;
    std::vector<int> preorder = {1, -1, 0, 3, 2, 4};
    bst.preorderTraversal(nodes);
    ASSERT_EQ(nodes.size(), preorder.size());
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        ASSERT_EQ(nodes[i]->getKey(), preorder[i]);
    }
}

TEST(MinGeneralParent, test_1)
{
    BST<int> bst;
    bst.add(0);
    bst.add(0);
    bst.add(0);
    ASSERT_EQ(bst.getMinGeneralParent(bst.find(0), bst.find(0))->getKey(), 0);
}

TEST(MinGeneralParent, test_2)
{
    BST<int> bst;
    bst.add(5);
    bst.add(4);
    bst.add(2);
    bst.add(1);
    bst.add(3);
    ASSERT_EQ(bst.getMinGeneralParent(bst.find(1), bst.find(3))->getKey(), 2);
}

TEST(MinGeneralParent, test_3)
{
    BST<int> bst;
    bst.add(5);
    bst.add(1);
    bst.add(2);
    bst.add(4);
    bst.add(3);
    bst.add(-1);
    bst.add(0);
    bst.add(7);
    bst.add(6);
    ASSERT_EQ(bst.getMinGeneralParent(bst.find(0), bst.find(2))->getKey(), 1);
}