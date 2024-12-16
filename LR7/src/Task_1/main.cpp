#include <iostream>
#include <string>

#include "tools.h"

int main() // O(n)
{
    std::string str;
    std::cout << "Binary in two's conversation: \t";
    std::cin >> str;
    unsigned short *array = string_to_array(str);
    twos_to_trivial(array, str.size());
    std::cout << "Binary in trivial approach: \t";
    for (size_t i = 0; i < str.size(); i++)
    {
        std::cout << array[i];
    }
    std::cout << std::endl;
    delete[] array;
    array = nullptr;
    return 0;
}