#ifndef STACK_H
#define STACK_H

#include <cstddef>

#include "deque.h"

template <typename T, std::size_t BLOCK_SIZE = 8>
class Stack : private Deque<T, BLOCK_SIZE>
{
public:
    using size_type = std::size_t;

    using Deque<T, BLOCK_SIZE>::size;
    using Deque<T, BLOCK_SIZE>::empty;
    using Deque<T, BLOCK_SIZE>::clear;
    using Deque<T, BLOCK_SIZE>::begin;
    using Deque<T, BLOCK_SIZE>::end;
    using Deque<T, BLOCK_SIZE>::operator=;

    T &top() { return Deque<T>::back(); }
    const T &top() const { return Deque<T>::back(); };
    void push(const T &value) { Deque<T>::push_back(value); }
    void pop() { Deque<T>::pop_back(); }
};

#endif  // STACK_H
