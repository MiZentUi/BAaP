#ifndef LIST_H
#define LIST_H

#include <memory>

template <typename T>
class List
{
private:
    struct Node
    {
        std::shared_ptr<Node> prev;
        T value;
        std::shared_ptr<Node> next;

        Node(T value) : value(value) {}
        Node(T value, Node *next) : value(value), next(next) {}
    };

    std::size_t _size{0};
    std::shared_ptr<Node> head;

public:
    List() {};
    List(const List &other);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;
    void add(const T &value);
    void remove(std::size_t index);

    T &operator[](std::size_t index);
    const T &operator[](std::size_t index) const;
};

template <typename T>
List<T>::List(const List<T> &other)
{
    head.reset();
    for (std::weak_ptr<Node> node = other.head; node.expired();
         node = node->next)
    {
        add(node->value);
    }
}

template <typename T>
std::size_t List<T>::size() const
{
    return _size;
}

template <typename T>
bool List<T>::empty() const
{
    return _size == 0;
}

template <typename T>
void List<T>::add(const T &value)
{
    if (!head)
    {
        head.reset(new Node(value));
        _size++;
        return;
    }
    std::weak_ptr<Node> node(head);
    while (node.lock()->next)
    {
        node = node.lock()->next;
    }
    node.lock()->next.reset(new Node(value));
    node.lock()->next->prev = node.lock();
    _size++;
}

template <typename T>
void List<T>::remove(std::size_t index)
{
    std::weak_ptr<Node> node = head;
    while ((bool)index--)
    {
        node = node.lock()->next;
    }
    std::weak_ptr<Node> next = node.lock()->next;
    std::weak_ptr<Node> prev = node.lock()->prev;
    if (prev.lock())
    {
        prev.lock()->next = next.lock();
    }
    if (next.lock())
    {
        next.lock()->prev = prev.lock();
    }
    node.reset();
    _size--;
}

template <typename T>
T &List<T>::operator[](std::size_t index)
{
    std::weak_ptr<Node> node = head;
    while (!node.expired() && (bool)index--)
    {
        node = node.lock()->next;
    }
    return node.lock()->value;
}

template <typename T>
const T &List<T>::operator[](std::size_t index) const
{
    std::weak_ptr<Node> node = head;
    while ((bool)index--)
    {
        node = node.lock()->next;
    }
    return node.lock()->value;
}

#endif  // LIST_H
