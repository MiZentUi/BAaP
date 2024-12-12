#include "tools.h"
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>

unsigned short * string_to_array(const std::string str)
{
    size_t s_size = str.size(); 
    auto *array = new unsigned short[s_size];
    for (size_t i = 0; i < s_size; i++)
    {
        array[i] = (unsigned short)(str[i] - '0');
    }
    return array;
}

void twos_to_trivial(unsigned short *array, size_t size)
{
    if (size > 0 && array[0] == 1)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (array[size - i - 1] == 0)
            {
                array[size - i - 1] = 1;
            }
            else
            {
                array[size - i - 1] = 0;
                break;
            }
        }
        for (size_t i = 1; i < size; i++) // O(n)
        {
            array[i] ^= 1; 
        }
    }
}

long long bin_len(long long n)
{
    if (n == 0)
    {
        return 0;
    }
    return (long long)std::floor(std::log2(n)) + 1;
}

void bin_add(unsigned short *&a_array, size_t a_size, unsigned short *&b_array, size_t b_size, unsigned short *&c_array, size_t &c_size)
{
    unsigned short add = 0;
    c_size = std::max(a_size, b_size) + 1;
    c_array = new unsigned short[c_size]{};
    for (size_t i = 0; i < c_size; i++)
    {
        unsigned short a_i = i < a_size - 1 ? a_array[a_size - i - 1] : a_array[0];
        unsigned short b_i = i < b_size - 1 ? b_array[b_size - i - 1] : b_array[0];
        unsigned short current_xor = (a_i ^ b_i) ^ add;
        add = (b_i + a_i + add > 1) ? 1 : 0;
        c_array[c_size - i - 1] = current_xor;
    }
}

void trivial_to_twos(unsigned short *&array, size_t &size)
{
    if (size > 0 && array[0] == 1)
    {
        for (size_t i = 1; i < size; i++)
        {
            array[i] ^= 1;
        }
        auto *temp_array = new unsigned short[size]{};
        temp_array[size - 1] = 1;
        unsigned short *res_array = nullptr;
        bin_add(array, size, temp_array, size, res_array, size);
        delete[] temp_array;
        temp_array = nullptr;
        delete[] array;
        array = res_array;
    }
}

void dec_to_bin(long long n, unsigned short *&array, size_t &size)
{
    long long temp = std::abs(n);
    size = bin_len(temp) + 1;
    array = new unsigned short[size];
    for (int i = 0; i < size; i++)
    {
        array[size - i - 1] = (unsigned short)(temp % 2);
        temp /= 2;
    }
    if (n < 0)
    {
        array[0] = 1;
    }
}

long long bin_to_dec(const unsigned short *array, size_t size)
{
    long long num = 0;
    for (int i = 0; i < size - 1; i++)
        if (array[size - i - 1] == 1)
            num += (long long)std::pow(2, i);
    if (array[0] == 1)
        return -num;
    return num;
}

char to_notation_symbol(int num)//2
{
    if (num > 9)
        return (char)(num + 'A' - 10);
    return (char)(num + '0');
}

int from_notation_symbol(char symbol)
{
    if (!(bool)std::isdigit(symbol))
        return std::toupper(symbol) - 'A' + 10;
    return symbol - '0';
}

std::string string_notation_addition(std::string str1, std::string str2, int base)
{
    std::string result;
    int add = 0;
    for (size_t i = 0; i < str1.size() || i < str2.size(); i++)
    {
        int num1 = i < str1.size() ? from_notation_symbol(str1[str1.size() - i - 1]) : 0;
        int num2 = i < str2.size() ? from_notation_symbol(str2[str2.size() - i - 1]) : 0;
        int sum = num1 + num2 + add;
        result = to_notation_symbol(sum % base) + result;
        add = sum / base;
    }
    if (add > 0)
        result = to_notation_symbol(add) + result;
    return result;
}

std::string string_notation_substract(std::string str1, std::string str2, int base)
{
    std::string result;
    int substract = 0;
    for (size_t i = 0; i < str1.size() || i < str2.size(); i++)
    {
        int num1 = i < str1.size() ? from_notation_symbol(str1[str1.size() - i - 1]) : 0;
        int num2 = i < str2.size() ? from_notation_symbol(str2[str2.size() - i - 1]) : 0;
        num2 += substract;
        if (num1 < num2)
        {
            num1 += base;
            substract = 1;
        }
        else
            substract = 0;
        result = to_notation_symbol(num1 - num2) + result;
    }
    int zeroes = 0;
    for (char symbol : result)
    {
        if (symbol != '0')
            break;
        zeroes++;
    }
    result.erase(0, zeroes);
    if (result.empty())
        result = '0';
    return result;
}

bool is_divide(long long num, long long divider) // O(log(n))
{
    long long magic_num = (divider + 1) >> 1;
    if (num < 0)
        num = ~num;
    while (num > divider)
    {
        if ((bool)(num & 1))
            num = magic_num + (num >> 1);
        else
            num >>= 1;
    }
    return num == divider;
}