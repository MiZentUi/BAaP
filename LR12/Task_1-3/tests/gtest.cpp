#include <gtest/gtest.h>

#include <memory>

#include "tools.h"

TEST(heap_sort, test_1)
{
    std::size_t size = 2;
    std::unique_ptr<int[]> array(new int[size]{2, 1});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2});
    heap_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(heap_sort, test_2)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{0, 0, 0, 0, 0});
    std::unique_ptr<int[]> sorted_array(new int[size]{0, 0, 0, 0, 0});
    heap_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(heap_sort, test_3)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{2, 4, 7, 100000, 6});
    std::unique_ptr<int[]> sorted_array(new int[size]{2, 4, 6, 7, 100000});
    heap_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(heap_sort, test_4)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{4, 5, 3, 1, 2});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2, 3, 4, 5});
    heap_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(heap_sort, test_5)
{
    std::size_t size = 0;
    std::unique_ptr<int[]> array(new int[size]{});
    std::unique_ptr<int[]> sorted_array(new int[size]{});
    heap_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(quick_sort, test_1)
{
    std::size_t size = 2;
    std::unique_ptr<int[]> array(new int[size]{2, 1});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2});
    quick_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(quick_sort, test_2)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{0, 0, 0, 0, 0});
    std::unique_ptr<int[]> sorted_array(new int[size]{0, 0, 0, 0, 0});
    quick_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(quick_sort, test_3)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{2, 4, 7, 100000, 6});
    std::unique_ptr<int[]> sorted_array(new int[size]{2, 4, 6, 7, 100000});
    quick_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(quick_sort, test_4)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{4, 5, 3, 1, 2});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2, 3, 4, 5});
    quick_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(quick_sort, test_5)
{
    std::size_t size = 0;
    std::unique_ptr<int[]> array(new int[size]{});
    std::unique_ptr<int[]> sorted_array(new int[size]{});
    quick_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(merge_sort, test_1)
{
    std::size_t size = 2;
    std::unique_ptr<int[]> array(new int[size]{2, 1});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(merge_sort, test_2)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{0, 0, 0, 0, 0});
    std::unique_ptr<int[]> sorted_array(new int[size]{0, 0, 0, 0, 0});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(merge_sort, test_3)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{2, 4, 7, 100000, 6});
    std::unique_ptr<int[]> sorted_array(new int[size]{2, 4, 6, 7, 100000});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(merge_sort, test_4)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{4, 5, 3, 1, 2});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2, 3, 4, 5});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(merge_sort, test_5)
{
    std::size_t size = 0;
    std::unique_ptr<int[]> array(new int[size]{});
    std::unique_ptr<int[]> sorted_array(new int[size]{});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(interpolation_sort, test_1)
{
    std::size_t size = 2;
    std::unique_ptr<int[]> array(new int[size]{2, 1});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2});
    interpolation_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(interpolation_sort, test_2)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{0, 0, 0, 0, 0});
    std::unique_ptr<int[]> sorted_array(new int[size]{0, 0, 0, 0, 0});
    interpolation_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(interpolation_sort, test_3)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{2, 4, 7, 100000, 6});
    std::unique_ptr<int[]> sorted_array(new int[size]{2, 4, 6, 7, 100000});
    merge_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(interpolation_sort, test_4)
{
    std::size_t size = 5;
    std::unique_ptr<int[]> array(new int[size]{4, 5, 3, 1, 2});
    std::unique_ptr<int[]> sorted_array(new int[size]{1, 2, 3, 4, 5});
    interpolation_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}

TEST(interpolation_sort, test_5)
{
    std::size_t size = 0;
    std::unique_ptr<int[]> array(new int[size]{});
    std::unique_ptr<int[]> sorted_array(new int[size]{});
    interpolation_sort(array, size);
    ASSERT_TRUE(
        std::equal(array.get(), array.get() + size, sorted_array.get()));
}