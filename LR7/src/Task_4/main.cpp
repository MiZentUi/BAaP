#include <iostream>
#include <string>

#include "tools.h"

const std::string ASCII_RESET =  "\x1b[0m";
const std::string ASCII_COLOR_RED = "\x1b[0;31m";
const std::string ASCII_COLOR_GREEN = "\x1b[0;32m";

int main() // O(log(n))
{
    long long num = 0;
    long long divider = 0;
    std::cout << "Write number: ";
    std::cin >> num;
    std::cout << "Write divider: ";
    std::cin >> divider;
    if (divider == 0)
    {
        std::cout << ASCII_COLOR_RED << "Zero division error!" << ASCII_RESET << std::endl;
        return 0;
    }
    std::cout << "Is divided: ";
    if (is_divide(num, divider))
        std::cout << ASCII_COLOR_GREEN << "true" << ASCII_RESET;
    else
        std::cout << ASCII_COLOR_RED << "false" << ASCII_RESET;
    std::cout << std::endl;
    return 0;
}