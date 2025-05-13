#ifndef STACKHASHTABLE_H
#define STACKHASHTABLE_H

#include <utility>

#include "stack.h"

template <typename K, typename V, std::size_t STACKS_SIZE = 8>
class StackHashTable
{
public:
    using size_type = std::size_t;

protected:
    size_type _size = 0;
    Stack<std::pair<K, V>> *_stacks;

public:
    StackHashTable();
    ~StackHashTable();

    size_type size();
    bool empty();
    bool contains(const K &key);
    void clear();

    V &operator[](const K &key);
};

template <typename K, typename V, std::size_t STACKS_SIZE>
StackHashTable<K, V, STACKS_SIZE>::StackHashTable()
    : _stacks(new Stack<std::pair<K, V>>[STACKS_SIZE] {})
{}

template <typename K, typename V, std::size_t STACKS_SIZE>
StackHashTable<K, V, STACKS_SIZE>::~StackHashTable()
{
    delete[] _stacks;
}

template <typename K, typename V, std::size_t STACKS_SIZE>
typename StackHashTable<K, V, STACKS_SIZE>::size_type
StackHashTable<K, V, STACKS_SIZE>::size()
{
    return _size;
}

template <typename K, typename V, std::size_t STACKS_SIZE>
bool StackHashTable<K, V, STACKS_SIZE>::empty()
{
    return _size == 0;
}

template <typename K, typename V, std::size_t STACKS_SIZE>
bool StackHashTable<K, V, STACKS_SIZE>::contains(const K &key)
{
    for (std::pair<K, V> &pair : _stacks[key % STACKS_SIZE])
    {
        if (pair.first == key)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V, std::size_t STACKS_SIZE>
void StackHashTable<K, V, STACKS_SIZE>::clear()
{
    for (size_type i = 0; i < STACKS_SIZE; i++)
    {
        _stacks[i].clear();
    }
}

template <typename K, typename V, std::size_t STACKS_SIZE>
V &StackHashTable<K, V, STACKS_SIZE>::operator[](const K &key)
{
    for (std::pair<K, V> &pair : _stacks[key % STACKS_SIZE])
    {
        if (pair.first == key)
        {
            return pair.second;
        }
    }
    _stacks[key % STACKS_SIZE].push({key, V()});
    _size++;
    return _stacks[key % STACKS_SIZE].top().second;
}

#endif  // STACKHASHTABLE_H
