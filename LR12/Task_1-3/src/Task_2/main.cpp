#include <iostream>

#include "tools.h"

int main(int argc, char const *argv[])
{
    std::size_t size = 0;
    std::cout << "Size: ";
    std::cin >> size;
    std::unique_ptr<int[]> array(new int[size]);
    std::cout << "Array: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }
    interpolation_sort(array, size, true);
    std::cout << "Sorted: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    int item = 0;
    std::cout << "Search: ";
    std::cin >> item;
    std::size_t index = interpolation_search(array, size, item);
    std::cout << "Index: ";
    if (index == -1)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        std::cout << index << std::endl;
        std::cout << "Binpow: " << binpow(index, size) << std::endl;
    }
    return 0;
}