#ifndef BST_H
#define BST_H

#include <vector>

template <typename K, typename V>
class BST
{
protected:
    struct Node
    {
        K key;
        V value;

        Node *left;
        Node *right;

        Node(K key, V value)
            : key(key), value(value), left(nullptr), right(nullptr)
        {}

        ~Node()
        {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
    };

    Node *getRoot();
    Node *insert(Node *node, const K &key, const V &value);
    Node *search(Node *node, const K &key);
    Node *remove(Node *node, const K &key);
    Node *minimum(Node *node);
    Node *buildBalancedBST(std::vector<std::pair<K, V>> &nodes, long long left,
                           long long right);
    void inorderTraversal(Node *node, std::vector<std::pair<K, V>> &nodes);
    void preorderTraversal(Node *node, std::vector<std::pair<K, V>> &nodes);
    void postorderTraversal(Node *node, std::vector<std::pair<K, V>> &nodes);

private:
    Node *root;

public:
    BST();
    ~BST();

    void balance();
    void insert(const K &key, const V &value);
    void remove(const K &key);
    V search(const K &key);
    void inorderTraversal(std::vector<std::pair<K, V>> &nodes);
    void preorderTraversal(std::vector<std::pair<K, V>> &nodes);
    void postorderTraversal(std::vector<std::pair<K, V>> &nodes);
};

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::getRoot()
{
    return root;
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::insert(Node *node, const K &key,
                                            const V &value)
{
    if (node == nullptr)
    {
        return new Node(key, value);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, value);
    }
    return node;
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::search(Node *node, const K &key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (key == node->key)
    {
        return node;
    }
    if (key < node->key)
    {
        return search(node->left, key);
    }
    return search(node->right, key);
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::remove(Node *node, const K &key)
{
    if (node == nullptr)
    {
        return node;
    }
    if (key < node->key)
    {
        node->left = remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key);
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        node->key = minimum(node->right)->key;
        node->right = remove(node->right, node->key);
    }
    else
    {
        if (node->left != nullptr)
        {
            node = node->left;
        }
        else if (node->right != nullptr)
        {
            node = node->right;
        }
        else
        {
            delete node;
            node = nullptr;
        }
    }
    return node;
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::minimum(Node *node)
{
    if (!node->left)
    {
        return node;
    }
    return minimum(node->left);
}

template <typename K, typename V>
typename BST<K, V>::Node *BST<K, V>::buildBalancedBST(
    std::vector<std::pair<K, V>> &nodes, long long left, long long right)
{
    if (left > right)
    {
        return nullptr;
    }
    long long middle = (left + right) / 2;
    auto *node = new Node(nodes[middle].first, nodes[middle].second);
    node->left = buildBalancedBST(nodes, left, middle - 1);
    node->right = buildBalancedBST(nodes, middle + 1, right);
    return node;
}

template <typename K, typename V>
void BST<K, V>::inorderTraversal(Node *node,
                                 std::vector<std::pair<K, V>> &nodes)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left, nodes);
        nodes.push_back({node->key, node->value});
        inorderTraversal(node->right, nodes);
    }
}

template <typename K, typename V>
void BST<K, V>::preorderTraversal(Node *node,
                                  std::vector<std::pair<K, V>> &nodes)
{
    if (node != nullptr)
    {
        nodes.push_back({node->key, node->value});
        preorderTraversal(node->left, nodes);
        preorderTraversal(node->right, nodes);
    }
}

template <typename K, typename V>
void BST<K, V>::postorderTraversal(Node *node,
                                   std::vector<std::pair<K, V>> &nodes)
{
    if (node != nullptr)
    {
        postorderTraversal(node->left, nodes);
        postorderTraversal(node->right, nodes);
        nodes.push_back({node->key, node->value});
    }
}

template <typename K, typename V>
BST<K, V>::BST() : root(nullptr)
{}

template <typename K, typename V>
BST<K, V>::~BST()
{
    delete root;
}

template <typename K, typename V>
void BST<K, V>::balance()
{
    std::vector<std::pair<K, V>> nodes;
    inorderTraversal(nodes);
    while (root != nullptr)
    {
        remove(root->key);
    }
    root = buildBalancedBST(nodes, 0, nodes.size() - 1);
}

template <typename K, typename V>
void BST<K, V>::insert(const K &key, const V &value)
{
    root = insert(root, key, value);
}

template <typename K, typename V>
void BST<K, V>::remove(const K &key)
{
    root = remove(root, key);
}

template <typename K, typename V>
V BST<K, V>::search(const K &key)
{
    Node *node = search(root, key);
    if (node == nullptr)
    {
        return V();
    }
    return node->value;
}

template <typename K, typename V>
void BST<K, V>::inorderTraversal(std::vector<std::pair<K, V>> &nodes)
{
    inorderTraversal(root, nodes);
}

template <typename K, typename V>
void BST<K, V>::preorderTraversal(std::vector<std::pair<K, V>> &nodes)
{
    preorderTraversal(root, nodes);
}

template <typename K, typename V>
void BST<K, V>::postorderTraversal(std::vector<std::pair<K, V>> &nodes)
{
    postorderTraversal(root, nodes);
}

#endif  // BST_H
