#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iterator>

#include "map.h"

template <typename K>
class Set : private Map<K, void>
{
public:
    using Map<K, void>::size;
    using Map<K, void>::empty;
    using Map<K, void>::contains;
    using Map<K, void>::remove;
    using Map<K, void>::clear;
    using Map<K, void>::begin;
    using Map<K, void>::end;
    using Map<K, void>::cbegin;
    using Map<K, void>::cend;

    Set() : Map<K, void>() {}

    void insert(const K &key) { insert(key); }
    K &min() { min(); }
    K &max() { max(); }
    const K &min() const { min(); }
    const K &max() const { max(); }
    std::vector<K> inorder() const
    {
        std::vector<std::pair<K, void>> entries = inorder();
        std::vector<K> keys;
        std::transform(entries.begin(), entries.end(), std::back_inserter(keys),
                       [](const std::pair<K, void> &pair)
                       { return pair.first; });
        return keys;
    }
};

#endif  // SET_H
