#include <iostream>
#include <string>

#include "tools.h"

int main()
{
    int base = 0;
    std::string str1;
    std::string str2;
    while (base < 2)
    {
        std::cout << "Base: \t\t";
        std::cin >> base;
        if (base < 2)
            std::cout << "Wrong base!" << std::endl;
    }
    std::cout << "First number: \t";
    std::cin >> str1;
    std::cout << "Second number: \t";
    std::cin >> str2;
    bool sign1 = str1[0] == '-';
    bool sign2 = str2[0] == '-';
    if (sign1)
        str1.erase(0, 1);
    if (sign2)
        str2.erase(0, 1);
    std::string addition = string_notation_addition(str1, str2, base);
    std::string substract = string_notation_substract(str1, str2, base);
    if (sign1 && sign2)
    {
        addition = '-' + addition;
        if (str1 > str2)
            substract = '-' + substract;
        else
            substract = string_notation_substract(str2, str1, base);
    }
    else if (!sign1 && !sign2)
    {
        if (str1 < str2)
        {
            substract = string_notation_substract(str2, str1, base);
            substract = '-' + substract;
        }
    }
    else if (sign1)
    {
        if (str2 < str1)
            addition = '-' + string_notation_substract(str1, str2, base);
        else
            addition = string_notation_substract(str2, str1, base);
        substract = '-' + string_notation_addition(str1, str2, base);
    }
    else
    {
        if (str1 < str2)
            addition = '-' + string_notation_substract(str2, str1, base);
        else
            addition = string_notation_substract(str1, str2, base);
        substract = string_notation_addition(str1, str2, base);
    }
    std::cout << "Addition: \t" << addition << std::endl;
    std::cout << "Substact: \t" << substract << std::endl;
    return 0;
}