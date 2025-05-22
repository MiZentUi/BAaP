#ifndef VECTORHEAP_H
#define VECTORHEAP_H

#include "vector.h"

template <typename T>
class VectorHeap : private Vector<T>
{
private:
    void shiftDown(std::size_t index);
    void shiftUp(std::size_t index);
    void heapify();

public:
    using Vector<T>::size;
    using Vector<T>::empty;
    using Vector<T>::remove;
    using Vector<T>::operator[];

    VectorHeap();
    VectorHeap(const Vector<T> &vector);

    T extractMin();
    void insert(const T &value);
    void merge(const VectorHeap<T> &heap);
};

template <typename T>
VectorHeap<T>::VectorHeap() : Vector<T>()
{}

template <typename T>
VectorHeap<T>::VectorHeap(const Vector<T> &vector) : Vector<T>(vector)
{
    heapify();
}

template <typename T>
void VectorHeap<T>::shiftDown(std::size_t index)
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
void VectorHeap<T>::shiftUp(std::size_t index)
{
    while (this->operator[](index) < this->operator[]((index - 1) / 2))
    {
        std::swap(this->operator[](index), this->operator[]((index - 1) / 2));
        index = (index - 1) / 2;
    }
}

template <typename T>
void VectorHeap<T>::heapify()
{
    std::size_t heapSize = this->size();
    for (std::size_t i = 0; i < heapSize / 2; i++)
    {
        shiftDown(heapSize / 2 - i - 1);
    }
}

template <typename T>
T VectorHeap<T>::extractMin()
{
    T temp = this->operator[](0);
    this->operator[](0) = this->operator[](this->size() - 1);
    this->remove(this->size() - 1);
    shiftDown(0);
    return temp;
}

template <typename T>
void VectorHeap<T>::insert(const T &value)
{
    this->push_back(value);
    shiftUp(this->size() - 1);
}

template <typename T>
void VectorHeap<T>::merge(const VectorHeap<T> &heap)
{
    for (std::size_t i = 0; i < heap.size(); i++)
    {
        this->push_back(heap.operator[](i));
    }
    heapify();
}

#endif  // VECTORHEAP_H
