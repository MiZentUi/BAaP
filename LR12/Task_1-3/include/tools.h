#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <iostream>
#include <memory>

template <typename T>
void heapify(std::unique_ptr<T[]> &array, std::size_t n, std::size_t index)
{
    std::size_t max = index;
    std::size_t left = 2 * index + 1;
    std::size_t right = left + 1;
    if (left < n && array[left] > array[max])
    {
        max = left;
    }
    if (right < n && array[right] > array[max])
    {
        max = right;
    }
    if (max != index)
    {
        std::swap(array[index], array[max]);
        heapify(array, n, max);
    }
}

template <typename T>
void heap_sort(std::unique_ptr<T[]> &array, std::size_t size)
{
    for (std::size_t i = 0; i < size / 2; i++)
    {
        heapify(array, size, size / 2 - i - 1);
    }
    for (std::size_t i = 0; i < size; i++)
    {
        std::swap(array[0], array[size - i - 1]);
        heapify(array, size - i - 1, 0);
    }
}

template <typename T>
std::size_t partition(std::unique_ptr<T[]> &array, std::size_t left,
                      std::size_t right)
{
    std::size_t middle = (left + right) / 2;
    while (left <= right)
    {
        while (array[left] < array[middle])
        {
            left++;
        }
        while (array[right] > array[middle] && right != 0)
        {
            right--;
        }
        if (left >= right)
        {
            break;
        }
        std::swap(array[left++], array[(right != 0) ? right-- : right]);
    }
    return right;
}

template <typename T>
void quick_sort(std::unique_ptr<T[]> &array, std::size_t size,
                std::size_t left = 0, std::size_t right = -1)
{
    if (right == -1)
    {
        right = size != 0 ? size - 1 : size;
    }
    if (left < right)
    {
        std::size_t delimeter = partition(array, left, right);
        quick_sort(array, size, left, delimeter);
        quick_sort(array, size, delimeter + 1, right);
    }
}

template <typename T>
void merge(std::unique_ptr<T[]> &array, std::size_t left, std::size_t middle,
           std::size_t right)
{
    std::unique_ptr<T[]> result(new T[right - left]);
    std::size_t left_iter = 0, right_iter = 0;
    while (left + left_iter < middle && middle + right_iter < right)
    {
        if (array[left + left_iter] < array[middle + right_iter])
        {
            result[left_iter + right_iter] = array[left + left_iter];
            left_iter++;
        }
        else
        {
            result[left_iter + right_iter] = array[middle + right_iter];
            right_iter++;
        }
    }
    while (left + left_iter < middle)
    {
        result[left_iter + right_iter] = array[left + left_iter];
        left_iter++;
    }
    while (middle + right_iter < right)
    {
        result[left_iter + right_iter] = array[middle + right_iter];
        right_iter++;
    }
    for (std::size_t i = 0; i < left_iter + right_iter; i++)
    {
        array[left + i] = result[i];
    }
}

template <typename T>
void merge_sort(std::unique_ptr<T[]> &array, std::size_t size)
{
    for (std::size_t i = 1; i < size; i *= 2)
    {
        for (std::size_t j = 0; j < size - i; j += i * 2)
        {
            merge(array, j, i + j, std::min(i * 2 + j, size));
        }
    }
}

template <typename T>
void interpolation_sort(std::unique_ptr<T[]> &array, std::size_t size,
                        bool print = false)
{
    if (size == 0)
    {
        return;
    }
    if (print)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
    std::size_t index = 0;
    std::size_t min = array[0];
    std::size_t max = array[0];
    for (std::size_t i = 1; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
        else if (array[i] > max)
            max = array[i];
    }
    if (min != max)
    {
        std::unique_ptr<std::size_t[]> bucket_sizes(new std::size_t[size]{});
        std::unique_ptr<std::unique_ptr<T[]>[]> bucket(
            new std::unique_ptr<T[]>[size]);
        for (std::size_t i = 0; i < size; i++)
        {
            bucket[i] = std::make_unique<T[]>(size);
        }
        for (std::size_t i = 0; i < size; i++)
        {
            std::size_t interpolation =
                ((array[i] - min) / (max - min)) * (size - 1);
            bucket[interpolation][bucket_sizes[interpolation]++] = array[i];
        }
        for (std::size_t i = 0; i < size; i++)
        {
            if (bucket_sizes[i] > 1)
            {
                interpolation_sort(bucket[i], bucket_sizes[i], print);
            }
            for (std::size_t j = 0; j < bucket_sizes[i]; j++)
            {
                array[index++] = bucket[i][j];
            }
        }
    }
}

template <typename T>
std::size_t bin_search(const std::unique_ptr<T[]> &array, std::size_t size,
                       T item)
{
    std::size_t left = 0;
    std::size_t right = size - 1;
    while (left <= right)
    {
        std::size_t middle = left + (right - left) / 2;
        if (array[middle] == item)
        {
            return middle;
        }
        if (array[middle] < item)
        {
            left = middle + 1;
        }
        else
        {
            right = middle != 0 ? middle - 1 : middle;
        }
    }
    return -1;
}

template <typename T>
std::size_t interpolation_search(const std::unique_ptr<T[]> &array,
                                 std::size_t size, T item)
{
    std::size_t left = 0;
    std::size_t right = size - 1;
    while (left < right && array[left] <= item && item <= array[right])
    {
        std::size_t middle;
        if (array[right] - array[left] != 0)
        {
            middle = left + ((item - array[left]) * (right - left)) /
                                (array[right] - array[left]);
        }
        else
        {
            middle = left + (right - left) / 2;
        }
        if (array[middle] == item)
        {
            return middle;
        }
        if (array[middle] < item)
        {
            left = middle + 1;
        }
        else
        {
            right = middle != 0 ? middle - 1 : middle;
        }
    }
    return -1;
}

template <typename T>
T binpow(T a, T n, const int mod = 1e9 + 7)
{
    T result = 1;
    while (n != 0)
    {
        if (n & 1)
            result *= a % mod;
        a *= a % mod;
        n >>= 1;
    }
    return result;
}

template <typename T>
void to_medians(std::unique_ptr<T[]> &array, std::size_t &size)
{
    for (std::size_t i = 0; i < size; i += 3)
    {
        if (size - i > 2)
        {
            quick_sort(array, size, i, i + 2);
            array[i / 3] = array[i + 1];
        }
        else
        {
            T sum = 0;
            for (std::size_t j = i; j < size; j++)
                sum += array[j];
            array[i / 3] = sum / (size - i);
        }
    }
    size = std::ceil(size / 3.0);
}

#endif  // TOOLS_H