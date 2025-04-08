#include <chrono>
#include <iostream>

#include "tools.h"

int main(int argc, char const *argv[])
{
    std::size_t size = 0;
    std::cout << "Size: ";
    std::cin >> size;
    std::unique_ptr<int[]> array(new int[size]);
    std::unique_ptr<int[]> sort_array(new int[size]);
    std::cout << "Array: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }

    std::copy(array.get(), array.get() + size, sort_array.get());
    auto begin = std::chrono::high_resolution_clock::now();
    heap_sort(sort_array, size);
    std::cout << "Heap sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::high_resolution_clock::now() - begin)
                     .count()
              << std::endl;

    std::copy(array.get(), array.get() + size, sort_array.get());
    begin = std::chrono::high_resolution_clock::now();
    quick_sort(sort_array, size);
    std::cout << "Quick sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::high_resolution_clock::now() - begin)
                     .count()
              << std::endl;

    std::copy(array.get(), array.get() + size, sort_array.get());
    begin = std::chrono::high_resolution_clock::now();
    merge_sort(sort_array, size);
    std::cout << "Merge sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     std::chrono::high_resolution_clock::now() - begin)
                     .count()
              << std::endl;

    std::copy(sort_array.get(), sort_array.get() + size, array.get());
    std::cout << "Sorted: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    int item = 0;
    std::cout << "Search: ";
    std::cin >> item;
    std::size_t index = bin_search(array, size, item);
    std::cout << "Index: ";
    if (index == -1)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << index;
    }
    std::cout << std::endl;
    return 0;
}