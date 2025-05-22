#include <gtest/gtest.h>

#include <vector>

#include "listheap.h"
#include "vectorheap.h"

TEST(VectorHeap, test_1)
{
    VectorHeap<int> heap;
    heap.insert(3);
    heap.insert(1);
    heap.insert(4);
    heap.insert(1);
    heap.insert(2);
    std::vector<int> sorted = {1, 1, 2, 3, 4};
    ASSERT_EQ(heap.size(), sorted.size());
    for (int value : sorted)
    {
        ASSERT_EQ(heap.extractMin(), value);
    }
    ASSERT_TRUE(heap.empty());
}

TEST(VectorHeap, test_2)
{
    VectorHeap<int> first_heap;
    first_heap.insert(5);
    first_heap.insert(4);
    first_heap.insert(3);
    VectorHeap<int> second_heap;
    second_heap.insert(2);
    second_heap.insert(1);
    first_heap.merge(second_heap);
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    ASSERT_EQ(first_heap.size(), sorted.size());
    for (int value : sorted)
    {
        ASSERT_EQ(first_heap.extractMin(), value);
    }
    ASSERT_TRUE(first_heap.empty());
}

TEST(ListHeap, test_1)
{
    ListHeap<int> heap;
    heap.insert(3);
    heap.insert(1);
    heap.insert(4);
    heap.insert(1);
    heap.insert(2);
    std::vector<int> sorted = {1, 1, 2, 3, 4};
    ASSERT_EQ(heap.size(), sorted.size());
    for (int value : sorted)
    {
        ASSERT_EQ(heap.extractMin(), value);
    }
    ASSERT_TRUE(heap.empty());
}

TEST(ListHeap, test_2)
{
    ListHeap<int> first_heap;
    first_heap.insert(5);
    first_heap.insert(4);
    first_heap.insert(3);
    ListHeap<int> second_heap;
    second_heap.insert(2);
    second_heap.insert(1);
    first_heap.merge(second_heap);
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    ASSERT_EQ(first_heap.size(), sorted.size());
    for (int value : sorted)
    {
        ASSERT_EQ(first_heap.extractMin(), value);
    }
    ASSERT_TRUE(first_heap.empty());
}