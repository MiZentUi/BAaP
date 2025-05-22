#ifndef BST_H
#define BST_H

#include <vector>

template <typename K>
class BST
{
public:
    class Node
    {
    private:
        friend class BST<K>;

        K key;

        Node *parent;
        Node *left;
        Node *right;

        void freeChilds()
        {
            if (left != nullptr)
            {
                left->freeChilds();
                delete left;
                left = nullptr;
            }
            if (right != nullptr)
            {
                right->freeChilds();
                delete right;
                right = nullptr;
            }
        }

    public:
        Node(K key) : key(key), parent(nullptr), left(nullptr), right(nullptr)
        {}
        Node(K key, Node *parent)
            : key(key), parent(parent), left(nullptr), right(nullptr)
        {}
        Node(const Node &other) : key(other->key) {}

        K getKey() { return key; }
        Node *getParent() { return parent; }
        Node *getLeft() { return left; }
        Node *getRight() { return right; }
    };

private:
    Node *root;

    Node *getRoot();
    Node *add(Node *parent_node, Node *next_node, const Node &node);
    Node *find(Node *parent_node, const K &key) const;
    Node *remove(Node *parent_node, const K &key);
    Node *minimum(Node *node) const;
    Node *buildBalancedBST(std::vector<Node *> &nodes, Node *parent_node,
                           long long left, long long right);
    void inorderTraversal(Node *node, std::vector<Node *> &nodes) const;
    void preorderTraversal(Node *node, std::vector<Node *> &nodes) const;
    void postorderTraversal(Node *node, std::vector<Node *> &nodes) const;
    std::pair<typename BST<K>::Node *, std::size_t> deepestNode(
        Node *node, std::size_t level = 0) const;

public:
    BST();
    ~BST();

    void balance();
    void add(const Node &node);
    void add(const K &key);
    Node *find(const K &key) const;
    void remove(const K &key);
    void inorderTraversal(std::vector<Node *> &nodes) const;
    void preorderTraversal(std::vector<Node *> &nodes) const;
    void postorderTraversal(std::vector<Node *> &nodes) const;
    void insertSubtree(const BST &subtree);
    void removeSubtree(const K &key);
    void removeBranch(Node *begin_node);
    void removeBranch(const K &key);
    std::vector<Node *> getPath(Node *node) const;
    Node *getMinGeneralParent(Node *first, Node *second) const;
};

template <typename K>
typename BST<K>::Node *BST<K>::getRoot()
{
    return root;
}

template <typename K>
typename BST<K>::Node *BST<K>::add(Node *parent_node, Node *next_node,
                                   const Node &node)
{
    if (next_node == nullptr)
    {
        return new Node(node.key, parent_node);
    }
    if (node.key < next_node->key)
    {
        next_node->left = add(next_node, next_node->left, node);
    }
    else if (node.key > next_node->key)
    {
        next_node->right = add(next_node, next_node->right, node);
    }
    return next_node;
}

template <typename K>
typename BST<K>::Node *BST<K>::find(Node *parent_node, const K &key) const
{
    if (parent_node == nullptr)
    {
        return nullptr;
    }
    if (key == parent_node->key)
    {
        return parent_node;
    }
    if (key < parent_node->key)
    {
        return find(parent_node->left, key);
    }
    return find(parent_node->right, key);
}

template <typename K>
typename BST<K>::Node *BST<K>::remove(Node *parent_node, const K &key)
{
    if (parent_node == nullptr)
    {
        return parent_node;
    }
    if (key < parent_node->key)
    {
        parent_node->left = remove(parent_node->left, key);
    }
    else if (key > parent_node->key)
    {
        parent_node->right = remove(parent_node->right, key);
    }
    else if (parent_node->left != nullptr && parent_node->right != nullptr)
    {
        parent_node->key = minimum(parent_node->right)->key;
        parent_node->right = remove(parent_node->right, parent_node->key);
    }
    else
    {
        if (parent_node->left != nullptr)
        {
            parent_node->left->parent = parent_node->parent;
            parent_node = parent_node->left;
        }
        else if (parent_node->right != nullptr)
        {
            parent_node->right->parent = parent_node->parent;
            parent_node = parent_node->right;
        }
        else
        {
            delete parent_node;
            parent_node = nullptr;
        }
    }
    return parent_node;
}

template <typename K>
typename BST<K>::Node *BST<K>::minimum(Node *node) const
{
    if (!node->left)
    {
        return node;
    }
    return minimum(node->left);
}

template <typename K>
typename BST<K>::Node *BST<K>::buildBalancedBST(std::vector<Node *> &nodes,
                                                Node *parent_node,
                                                long long left, long long right)
{
    if (left > right)
    {
        return nullptr;
    }
    long long middle = (left + right) / 2;
    auto *node = new Node(*nodes[middle]);
    node->parent = parent_node;
    node->left = buildBalancedBST(nodes, node, left, middle - 1);
    node->right = buildBalancedBST(nodes, node, middle + 1, right);
    return node;
}

template <typename K>
void BST<K>::inorderTraversal(Node *parent_node,
                              std::vector<Node *> &nodes) const
{
    if (parent_node != nullptr)
    {
        inorderTraversal(parent_node->left, nodes);
        nodes.push_back(parent_node);
        inorderTraversal(parent_node->right, nodes);
    }
}

template <typename K>
void BST<K>::preorderTraversal(Node *parent_node,
                               std::vector<Node *> &nodes) const
{
    if (parent_node != nullptr)
    {
        nodes.push_back(parent_node);
        preorderTraversal(parent_node->left, nodes);
        preorderTraversal(parent_node->right, nodes);
    }
}

template <typename K>
void BST<K>::postorderTraversal(Node *parent_node,
                                std::vector<Node *> &nodes) const
{
    if (parent_node != nullptr)
    {
        postorderTraversal(parent_node->left, nodes);
        postorderTraversal(parent_node->right, nodes);
        nodes.push_back(parent_node);
    }
}

template <typename K>
std::pair<typename BST<K>::Node *, std::size_t> BST<K>::deepestNode(
    Node *node, std::size_t level) const
{
    if (node->left == nullptr && node->right == nullptr)
    {
        return {node, level};
    }
    std::pair<Node *, std::size_t> node1 = {nullptr, 0};
    std::pair<Node *, std::size_t> node2 = {nullptr, 0};
    if (node->left != nullptr)
    {
        node1 = deepestNode(node->left, level + 1);
    }
    if (node->right != nullptr)
    {
        node2 = deepestNode(node->right, level + 1);
        if (node2.second > node1.second)
        {
            return node2;
        }
    }
    return node1;
}

template <typename K>
BST<K>::BST() : root(nullptr)
{}

template <typename K>
BST<K>::~BST()
{
    if (root != nullptr)
    {
        root->freeChilds();
        delete root;
        root = nullptr;
    }
}

template <typename K>
void BST<K>::balance()
{
    std::vector<K> nodes;
    inorderTraversal(nodes);
    while (root != nullptr)
    {
        remove(root->key);
    }
    root = buildBalancedBST(nodes, 0, nodes.size() - 1);
}

template <typename K>
void BST<K>::add(const Node &node)
{
    root = add(nullptr, root, node);
}

template <typename K>
void BST<K>::add(const K &key)
{
    root = add(nullptr, root, Node(key));
}

template <typename K>
typename BST<K>::Node *BST<K>::find(const K &key) const
{
    return find(root, key);
}

template <typename K>
void BST<K>::remove(const K &key)
{
    root = remove(root, key);
}

template <typename K>
void BST<K>::inorderTraversal(std::vector<Node *> &nodes) const
{
    inorderTraversal(root, nodes);
}

template <typename K>
void BST<K>::preorderTraversal(std::vector<Node *> &nodes) const
{
    preorderTraversal(root, nodes);
}

template <typename K>
void BST<K>::postorderTraversal(std::vector<Node *> &nodes) const
{
    postorderTraversal(root, nodes);
}

template <typename K>
void BST<K>::insertSubtree(const BST &subtree)
{
    std::vector<Node *> nodes;
    subtree.preorderTraversal(nodes);
    for (Node *node : nodes)
    {
        add(*node);
    }
}

template <typename K>
void BST<K>::removeSubtree(const K &key)
{
    Node *node = find(key);
    if (node != nullptr)
    {
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
            {
                node->parent->left = nullptr;
            }
            else
            {
                node->parent->right = nullptr;
            }
        }
        node->freeChilds();
    }
    remove(key);
}

template <typename K>
void BST<K>::removeBranch(Node *begin_node)
{
    Node *end_node = deepestNode(begin_node).first;
    while (begin_node != end_node)
    {
        Node *temp = end_node->parent;
        remove(end_node->key);
        end_node = temp;
    }
    remove(begin_node->key);
}

template <typename K>
void BST<K>::removeBranch(const K &key)
{
    removeBranch(find(key));
}

template <typename K>
std::vector<typename BST<K>::Node *> BST<K>::getPath(Node *node) const
{
    if (node != nullptr)
    {
        std::vector<Node *> nodes = getPath(node->parent);
        nodes.push_back(node);
        return nodes;
    }
    return {};
}

template <typename K>
typename BST<K>::Node *BST<K>::getMinGeneralParent(Node *first,
                                                   Node *second) const
{
    std::vector<Node *> first_path = getPath(first);
    std::vector<Node *> second_path = getPath(second);
    first_path.erase(first_path.end());
    second_path.erase(second_path.end());
    if (first_path.size() > second_path.size())
    {
        std::swap(first_path, second_path);
    }
    Node *node = root;
    for (Node *first_node : first_path)
    {
        bool contains = false;
        for (const Node *second_node : first_path)
        {
            if (first_node == second_node)
            {
                contains = true;
                break;
            }
        }
        if (contains && first_node->key < root->key)
        {
            node = first_node;
        }
    }
    return node;
}

#endif  // BST_H