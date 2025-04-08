#include <iostream>
#include <memory>

#include "tools.h"

int main(int argc, char const *argv[])
{
    std::size_t size = 0;
    std::cout << "Size: ";
    std::cin >> size;
    std::unique_ptr<long double[]> array(new long double[size]);
    std::cout << "Array: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }
    to_medians(array, size);
    std::cout << "Medians: ";
    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
