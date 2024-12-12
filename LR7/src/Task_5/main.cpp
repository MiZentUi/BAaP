#include <cstring>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

const std::string ASCII_RESET =  "\x1b[0m";
const std::string ASCII_COLOR_RED = "\x1b[0;31m";
const std::string ASCII_COLOR_GREEN = "\x1b[0;32m";
const std::string ASCII_COLOR_YELLOW = "\x1b[0;33m";

bool check_exist(const int *array, int size, int item) // O(n)
{
    for (int i = 0; i < size; i++)
        if (array[i] == item)
            return true;
    return false;
}

std::string array_to_string(const int *array, int size, int poisoned_barrel = -1) // O(n)
{
    std::stringstream sstream;
    sstream << std::setfill(' ') << std::setw(4);
    for (int i = 0; i < size; i++)
    {
        if (array[i] == poisoned_barrel)
            sstream << ASCII_COLOR_RED << array[i] << ASCII_RESET << ' ';
        else
            sstream << array[i] << ' ';
    }
    return sstream.str();
}

int get_one_barrel(int *array, int size, int slaves_count, int poisoned_barrel) // O(n * m)
{
    const int buffer_size = size / 2;
    auto *buffer = new int * [slaves_count];
    for (int i = 0; i < slaves_count; i++)
        buffer[i] = new int[buffer_size]{};
    auto *buffer_indexes = new unsigned int[slaves_count]{};
    memset(buffer_indexes, 0, slaves_count * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        int temp = i + 1;
        for (int j = 0; j < slaves_count && temp != 0; j++)
        {
            if (temp % 2 == 1)
            {
                buffer[j][buffer_indexes[j]++] = array[i];
            }
            temp /= 2;
        }
    }

    for (int i = 0; i < slaves_count; i++)
        std::cout << "Slave " << i + 1 << ": \t" << array_to_string(buffer[i], buffer_size, poisoned_barrel) << std::endl;

    std::cout << "After another 24 hours\n";

    int result = 0;
    std::cout << "Slaves status: \n";
    for (int i = 0; i < slaves_count; i++)
    {
        std::cout << i + 1 << ") ";
        if (check_exist(buffer[i], buffer_size, poisoned_barrel))
        {
            result += (int)std::pow(2, i);
            std::cout << ASCII_COLOR_RED << "dead" << ASCII_RESET;
        }
        else
            std::cout << ASCII_COLOR_GREEN << "alive" << ASCII_RESET;
        std::cout << std::endl;
    }
    for (int i = 0; i < slaves_count; i++)
        delete[] buffer[i];
    delete[] buffer;
    buffer = nullptr;
    delete[] buffer_indexes;
    buffer_indexes = nullptr;
    return array[result];
}

int main() // O(1)
{
    int poisoned_barrel = -1;
    std::cout << "Poisoned barrel (1 - 240): ";
    std::cin >> poisoned_barrel;
    if (poisoned_barrel <= 0 && 240 > poisoned_barrel)
    {
        std::cout << "Wrong barrel!";
        return 0;
    }
    const int slaves_count = 5;
    const int buffer_size = 80;
    const int rest_size = 30;
    bool slaves[slaves_count] = {true, true, true, true, true};
    int **buffer = new int * [slaves_count];
    for (int i = 0; i < slaves_count; i++)
        buffer[i] = new int[buffer_size]{};
    int *buffer_indexes = new int[slaves_count]{};
    memset(buffer_indexes, 0, slaves_count * sizeof(int));

    int *rest = new int[rest_size]{};
    int barrel_index = 1;
    int result = 0;

    for (int i = 0; i < slaves_count; i++)
        for (int j = 0; j < 16; j++)
        {
            buffer[i][buffer_indexes[i]++] = barrel_index;
            barrel_index++;
        }

    for (int i = 0; i < slaves_count; i++)
        for (int j = i + 1; j < slaves_count; j++)
            for (int k = 0; k < 8; k++)
            {
                buffer[i][buffer_indexes[i]++] = barrel_index;
                buffer[j][buffer_indexes[j]++] = barrel_index;
                barrel_index++;
            }

    for (int i = 0; i < slaves_count; i++)
        for (int j = i + 1; j < slaves_count; j++)
            for (int k = j + 1; k < slaves_count; k++)
                for (int l_i = 0; l_i < 4; l_i++)
                {
                    buffer[i][buffer_indexes[i]++] = barrel_index;
                    buffer[j][buffer_indexes[j]++] = barrel_index;
                    buffer[k][buffer_indexes[k]++] = barrel_index;
                    barrel_index++;
                }

    for (int i = 0; i < slaves_count; i++)
        for (int j = i + 1; j < slaves_count; j++)
            for (int k = j + 1; k < slaves_count; k++)
                for (int l_i = k + 1; l_i < slaves_count; l_i++)
                    for (int m_i = 0; m_i < 2; m_i++)
                    {
                        buffer[i][buffer_indexes[i]++] = barrel_index;
                        buffer[j][buffer_indexes[j]++] = barrel_index;
                        buffer[k][buffer_indexes[k]++] = barrel_index;
                        buffer[l_i][buffer_indexes[l_i]++] = barrel_index;
                        barrel_index++;
                    }
    
    for (int i = 0; i < 30 && barrel_index <= 240; i++)
        rest[i] = barrel_index++;

    for (int i = 0; i < slaves_count; i++)
        std::cout << "Slave " << i + 1 << ": \t" << array_to_string(buffer[i], buffer_size, poisoned_barrel) << std::endl;
    std::cout << "Rest: \t\t" << array_to_string(rest, rest_size, poisoned_barrel) << std::endl;

    int dead_count = 0;
    for (int i = 0; i < slaves_count; i++)
    {
        if (check_exist(buffer[i], buffer_size, poisoned_barrel))
        {
            slaves[i] = false;
            dead_count++;
        }
    }
    std::cout << "After 24 hours\n";
    std::cout << "Slaves status: \n";
    for (int i = 0; i < slaves_count; i++)
    {
        std::cout << i + 1 << ") ";
        if (slaves[i])
            std::cout << ASCII_COLOR_GREEN << "alive" << ASCII_RESET;
        else
            std::cout << ASCII_COLOR_RED << "dead" << ASCII_RESET;
        std::cout << std::endl;
    }

    std::cout << "Rest: \t\t";
    if (dead_count == 0)
    {
        std::cout << array_to_string(rest, rest_size, poisoned_barrel) << std::endl << std::endl;
        result = get_one_barrel(rest, 30, 5, poisoned_barrel);
    }
    else
    {
        int size = (int)std::pow(2, slaves_count - dead_count);
        int *intersection = new int[size]{};
        int index = 0;
        for (int i = 0; i < slaves_count; i++)
        {
            if (!slaves[i])
            {
                for (int j = 0; j < buffer_size; j++)
                {
                    bool all_exist = true;
                    for (int k = 0; k < slaves_count; k++)
                        if (k == i)
                            continue;
                        else if (!slaves[k])
                        {
                            if (!check_exist(buffer[k], buffer_size, buffer[i][j]))
                                all_exist = false;
                        }
                        else
                            if (check_exist(buffer[k], buffer_size, buffer[i][j]))
                                all_exist = false;
                    if (all_exist)
                        intersection[index++] = buffer[i][j];
                }
                break;
            }
        }
        std::cout << array_to_string(intersection, size) << std::endl << std::endl;
        result = get_one_barrel(intersection, size, slaves_count - dead_count, poisoned_barrel);
        delete[] intersection;
    }
    std::cout << "Poisoned barrel: " << result << std::endl;
    for (int i = 0; i < slaves_count; i++)
        delete[] buffer[i];
    delete[] buffer;
    buffer = nullptr;
    delete[] rest;
    rest = nullptr;
    delete[] buffer_indexes;
    buffer_indexes = nullptr;
    return 0;
}