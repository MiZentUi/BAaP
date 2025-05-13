#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

#include "deque.h"

template <typename T, std::size_t BLOCK_SIZE = 8>
class Queue : private Deque<T, BLOCK_SIZE>
{
public:
    using size_type = unsigned long long;

    using Deque<T, BLOCK_SIZE>::size;
    using Deque<T, BLOCK_SIZE>::empty;
    using Deque<T, BLOCK_SIZE>::clear;
    using Deque<T, BLOCK_SIZE>::front;
    using Deque<T, BLOCK_SIZE>::back;
    using Deque<T, BLOCK_SIZE>::operator=;

    void push(const T &value) { Deque<T>::push_back(value); }
    void pop() { Deque<T>::pop_front(); }
};

#endif  // QUEUE_H
