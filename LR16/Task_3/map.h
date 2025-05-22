#ifndef MAP_H
#define MAP_H

#include <memory>
#include <utility>
#include <vector>

template <typename K, typename V>
class Map
{
protected:
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        std::pair<const K, V> entry;
        Color color;
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(std::pair<K, V> entry) : entry(entry), color(RED) {}
    };

    std::shared_ptr<Node> getRoot();

private:
    template <typename NODE>
    class MapIterator
    {
    private:
        friend class Map;

        std::shared_ptr<NODE> node;

        MapIterator(std::shared_ptr<NODE> node) : node(node) {}

        std::shared_ptr<NODE> operator->() { return node; }

    public:
        std::pair<K, V> operator*() { return node->entry; }
        bool operator==(const MapIterator &iter) { return node == iter.node; }
        bool operator!=(const MapIterator &iter) { return !(*this == iter); }
        MapIterator<NODE> &operator++()
        {
            if (node && node->right)
            {
                node = node->right;
                while (node->left)
                {
                    node = node->left;
                }
            }
            else
            {
                while (node && node->parent && node->parent->left != node)
                {
                    node = node->parent;
                }
                if (node)
                {
                    node = node->parent;
                }
            }
            return *this;
        }
        MapIterator<NODE> operator++(int)
        {
            MapIterator<NODE> temp(*this);
            this->operator++();
            return temp;
        }
        MapIterator<NODE> &operator--()
        {
            if (node && node->left)
            {
                node = node->left;
                while (node->right)
                {
                    node = node->right;
                }
            }
            else
            {
                while (node && node->parent && node->parent->right != node)
                {
                    node = node->parent;
                }
                if (node)
                {
                    node = node->parent;
                }
            }
            return *this;
        }
        MapIterator<NODE> operator--(int)
        {
            MapIterator<NODE> temp(*this);
            this->operator--();
            return temp;
        }
    };

    std::size_t _size = 0;
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> search(std::shared_ptr<Node> node,
                                 const K &key) const;
    std::shared_ptr<Node> minNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> maxNode(std::shared_ptr<Node> node);

    void leftRotate(std::shared_ptr<Node> node);
    void rightRotate(std::shared_ptr<Node> node);
    void deleteNode(std::shared_ptr<Node> node);
    void fixInsert(std::shared_ptr<Node> node);
    void fixDelete(std::shared_ptr<Node> node);
    void transplant(std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    void inorderTraversal(std::shared_ptr<Node> node,
                          std::vector<std::pair<K, V>> &entries) const;

public:
    using iterator = MapIterator<Node>;
    using const_iterator = MapIterator<const Node>;

    Map() = default;
    ~Map();

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool contains(const K &key) const;
    void insert(const K &key);
    void insert(const std::pair<K, V> &entry);
    void remove(const K &key);
    void clear();
    std::pair<const K, V> &min();
    std::pair<const K, V> &max();
    const std::pair<const K, V> &min() const;
    const std::pair<const K, V> &max() const;
    std::vector<std::pair<K, V>> inorder() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    V &operator[](const K &key);
    const V &operator[](const K &key) const;
};

template <typename K, typename V>
std::shared_ptr<typename Map<K, V>::Node> Map<K, V>::getRoot()
{
    return root;
}

template <typename K, typename V>
std::shared_ptr<typename Map<K, V>::Node> Map<K, V>::search(
    std::shared_ptr<Node> node, const K &key) const
{
    if (!node)
    {
        return node;
    }
    if (key == node->entry.first)
    {
        return node;
    }
    if (key < node->entry.first)
    {
        return search(node->left, key);
    }
    return search(node->right, key);
}

template <typename K, typename V>
std::shared_ptr<typename Map<K, V>::Node> Map<K, V>::minNode(
    std::shared_ptr<Node> node)
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

template <typename K, typename V>
std::shared_ptr<typename Map<K, V>::Node> Map<K, V>::maxNode(
    std::shared_ptr<Node> node)
{
    while (node && node->right)
    {
        node = node->right;
    }
    return node;
}

template <typename K, typename V>
void Map<K, V>::leftRotate(std::shared_ptr<Node> node)
{
    if (!node || !node->right)
    {
        return;
    }
    std::shared_ptr<Node> right_node = node->right;
    node->right = right_node->left;
    if (right_node->left)
    {
        right_node->left->parent = node;
    }
    right_node->parent = node->parent;
    if (!node->parent)
    {
        root = right_node;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right_node;
    }
    else
    {
        node->parent->right = right_node;
    }
    right_node->left = node;
    node->parent = right_node;
}

template <typename K, typename V>
void Map<K, V>::rightRotate(std::shared_ptr<Node> node)
{
    if (!node || !node->left)
    {
        return;
    }
    std::shared_ptr<Node> left_node = node->left;
    node->left = left_node->right;
    if (left_node->right)
    {
        left_node->right->parent = node;
    }
    left_node->parent = node->parent;
    if (!node->parent)
    {
        root = left_node;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = left_node;
    }
    else
    {
        node->parent->right = left_node;
    }
    left_node->right = node;
    node->parent = left_node;
}

template <typename K, typename V>
void Map<K, V>::deleteNode(std::shared_ptr<Node> node)
{
    if (!node)
    {
        return;
    }
    std::shared_ptr<Node> first_node = node;
    std::shared_ptr<Node> second_node;
    Color first_color = first_node->color;
    if (!node->left)
    {
        second_node = node->right;
        transplant(node, node->right);
    }
    else if (!node->right)
    {
        second_node = node->left;
        transplant(node, node->left);
    }
    else
    {
        first_node = minNode(node->right);
        first_color = first_node->color;
        second_node = first_node->right;
        if (first_node->parent == node)
        {
            if (second_node)
            {
                second_node->parent = first_node;
            }
        }
        else
        {
            if (second_node)
            {
                second_node->parent = first_node->parent;
            }
            transplant(first_node, first_node->right);
            if (first_node->right)
            {
                first_node->right->parent = first_node;
            }
            first_node->right = node->right;
            if (first_node->right)
            {
                first_node->right->parent = first_node;
            }
        }
        transplant(node, first_node);
        first_node->left = node->left;
        if (first_node->left)
        {
            first_node->left->parent = first_node;
        }
        first_node->color = node->color;
    }
    if (first_color == BLACK && second_node)
    {
        fixDelete(second_node);
    }
}

template <typename K, typename V>
void Map<K, V>::fixInsert(std::shared_ptr<Node> node)
{
    while (node != root && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            std::shared_ptr<Node> uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        }
        else
        {
            std::shared_ptr<Node> uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename K, typename V>
void Map<K, V>::fixDelete(std::shared_ptr<Node> node)
{
    while (node != root && node && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            std::shared_ptr<Node> sibling = node->parent->right;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }
            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK))
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (!sibling->right || sibling->right->color == BLACK)
                {
                    if (sibling->left)
                    {
                        sibling->left->color = BLACK;
                    }
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right)
                {
                    sibling->right->color = BLACK;
                }
                leftRotate(node->parent);
                node = root;
            }
        }
        else
        {
            std::shared_ptr<Node> sibling = node->parent->left;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }
            if ((!sibling->right || sibling->right->color == BLACK) &&
                (!sibling->left || sibling->left->color == BLACK))
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (!sibling->left || sibling->left->color == BLACK)
                {
                    if (sibling->right)
                    {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left)
                {
                    sibling->left->color = BLACK;
                }
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    if (node)
    {
        node->color = BLACK;
    }
}

template <typename K, typename V>
void Map<K, V>::transplant(std::shared_ptr<Node> left,
                           std::shared_ptr<Node> right)
{
    if (!left->parent)
    {
        root = right;
    }
    else if (left == left->parent->left)
    {
        left->parent->left = right;
    }
    else
    {
        left->parent->right = right;
    }
    if (right)
    {
        right->parent = left->parent;
    }
}

template <typename K, typename V>
void Map<K, V>::inorderTraversal(std::shared_ptr<Node> node,
                                 std::vector<std::pair<K, V>> &entries) const
{
    if (node)
    {
        inorderTraversal(node->left, entries);
        entries.push_back(node->entry);
        inorderTraversal(node->right, entries);
    }
}

template <typename K, typename V>
Map<K, V>::~Map()
{
    root.reset();
}

template <typename K, typename V>
std::size_t Map<K, V>::size() const
{
    return _size;
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return _size == 0;
}

template <typename K, typename V>
bool Map<K, V>::contains(const K &key) const
{
    return (bool)search(root, key);
}

template <typename K, typename V>
void Map<K, V>::insert(const K &key)
{
    insert({key, V()});
}

template <typename K, typename V>
void Map<K, V>::insert(const std::pair<K, V> &entry)
{
    std::shared_ptr<Node> node = search(root, entry.first);
    if (node)
    {
        node->entry.second = entry.second;
        return;
    }
    node = std::shared_ptr<Node>(new Node(entry));
    std::shared_ptr<Node> first_node = root;
    std::shared_ptr<Node> second_node;
    while (first_node)
    {
        second_node = first_node;
        if (node->entry.first < first_node->entry.first)
        {
            first_node = first_node->left;
        }
        else
        {
            first_node = first_node->right;
        }
    }
    node->parent = second_node;
    if (!second_node)
    {
        root = node;
    }
    else if (node->entry.first < second_node->entry.first)
    {
        second_node->left = node;
    }
    else
    {
        second_node->right = node;
    }
    _size++;
    fixInsert(node);
}

template <typename K, typename V>
void Map<K, V>::remove(const K &key)
{
    deleteNode(search(root, key));
}

template <typename K, typename V>
void Map<K, V>::clear()
{
    _size = 0;
    root.reset();
}

template <typename K, typename V>
std::pair<const K, V> &Map<K, V>::min()
{
    return minNode(root)->entry;
}

template <typename K, typename V>
std::pair<const K, V> &Map<K, V>::max()
{
    return maxNode(root)->entry;
}

template <typename K, typename V>
const std::pair<const K, V> &Map<K, V>::min() const
{
    return minNode(root)->entry;
}

template <typename K, typename V>
const std::pair<const K, V> &Map<K, V>::max() const
{
    return maxNode(root)->entry;
}

template <typename K, typename V>
std::vector<std::pair<K, V>> Map<K, V>::inorder() const
{
    std::vector<std::pair<K, V>> entries;
    inorderTraversal(root, entries);
    return entries;
}

template <typename K, typename V>
typename Map<K, V>::iterator Map<K, V>::begin()
{
    return iterator(minNode(root));
}

template <typename K, typename V>
typename Map<K, V>::iterator Map<K, V>::end()
{
    return ++iterator(maxNode(root));
}

template <typename K, typename V>
typename Map<K, V>::const_iterator Map<K, V>::begin() const
{
    return const_iterator(minNode(root));
}

template <typename K, typename V>
typename Map<K, V>::const_iterator Map<K, V>::end() const
{
    return ++const_iterator(maxNode(root));
}

template <typename K, typename V>
typename Map<K, V>::const_iterator Map<K, V>::cbegin() const noexcept
{
    return const_iterator(minNode(root));
}

template <typename K, typename V>
typename Map<K, V>::const_iterator Map<K, V>::cend() const noexcept
{
    return ++const_iterator(maxNode(root));
}

template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    std::shared_ptr<Node> node = search(root, key);
    if (!node)
    {
        insert(key);
        node = search(root, key);
    }
    return node->entry.second;
}

template <typename K, typename V>
const V &Map<K, V>::operator[](const K &key) const
{
    std::shared_ptr<Node> node = search(root, key);
    if (!node)
    {
        insert(key);
        node = search(root, key);
    }
    return node->entry.second;
}

#endif  // MAP_H