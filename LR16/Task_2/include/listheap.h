#ifndef LISTHEAP_H
#define LISTHEAP_H

#include <utility>

#include "list.h"

template <typename T>
class ListHeap : private List<T>
{
private:
    void shiftDown(std::size_t index);
    void shiftUp(std::size_t index);
    void heapify();

public:
    using List<T>::size;
    using List<T>::empty;
    using List<T>::operator[];

    ListHeap();
    ListHeap(const List<T> &list);

    T extractMin();
    void insert(const T &value);
    void merge(const ListHeap<T> &heap);
};

template <typename T>
ListHeap<T>::ListHeap() : List<T>()
{}

template <typename T>
ListHeap<T>::ListHeap(const List<T> &list) : List<T>(list)
{
    heapify();
}

template <typename T>
void ListHeap<T>::shiftDown(std::size_t index)
{
    std::size_t heapSize = this->size();
    while (2 * index + 1 < heapSize)
    {
        std::size_t left = 2 * index + 1;
        std::size_t right = left + 1;
        std::size_t temp_index = left;
        if (right < heapSize &&
            this->operator[](right) < this->operator[](left))
        {
            temp_index = right;
        }
        if (this->operator[](index) <= this->operator[](temp_index))
        {
            break;
        }
        std::swap(this->operator[](index), this->operator[](temp_index));
        index = temp_index;
    }
}

template <typename T>
void ListHeap<T>::shiftUp(std::size_t index)
{
    while (index > 0 &&
           this->operator[](index) < this->operator[]((index - 1) / 2))
    {
        std::swap(this->operator[](index), this->operator[]((index - 1) / 2));
        index = (index - 1) / 2;
    }
}

template <typename T>
void ListHeap<T>::heapify()
{
    std::size_t heapSize = this->size();
    for (std::size_t i = 0; i < heapSize / 2; i++)
    {
        shiftDown(heapSize / 2 - i - 1);
    }
}

template <typename T>
T ListHeap<T>::extractMin()
{
    T temp = this->operator[](0);
    this->operator[](0) = this->operator[](this->size() - 1);
    this->remove(this->size() - 1);
    shiftDown(0);
    return temp;
}

template <typename T>
void ListHeap<T>::insert(const T &value)
{
    this->add(value);
    shiftUp(this->size() - 1);
}

template <typename T>
void ListHeap<T>::merge(const ListHeap<T> &heap)
{
    for (std::size_t i = 0; i < heap.size(); i++)
    {
        this->add(heap[i]);
    }
    heapify();
}

#endif  // LISTHEAP_H